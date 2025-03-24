#include "AssemblyInstruction.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <unordered_set>

// Метод для изменения размера массива
//  Переписать с  std::copy (algorithm)
void AssemblyInstruction::resize(int newCapacity) {
    Detail* newDetails = new Detail[newCapacity];
    for (int i = 0; i < detailCount; ++i) {
        newDetails[i] = details[i];
    }
    if (details != nullptr)
        delete[] details;
    details = newDetails;
    capacity = newCapacity;
}

// Конструктор по умолчанию
AssemblyInstruction::AssemblyInstruction() : details(nullptr), detailCount(0), capacity(0) {}

// Конструктор с массивом деталей
AssemblyInstruction::AssemblyInstruction(const Detail* detailArray, int count) : detailCount(count), capacity(count) {
    details = new Detail[capacity];
    for (int i = 0; i < detailCount; ++i) {
        details[i] = detailArray[i];
    }
}

// Копирующий конструктор
// algorithm
AssemblyInstruction::AssemblyInstruction(const AssemblyInstruction& other) : detailCount(other.detailCount), capacity(other.capacity) {
    details = new Detail[capacity];
    for (int i = 0; i < detailCount; ++i) {
        details[i] = other.details[i];
    }
}

// Перемещающий конструктор
AssemblyInstruction::AssemblyInstruction(AssemblyInstruction&& other) noexcept : details(other.details), detailCount(other.detailCount), capacity(other.capacity) {
    other.details = nullptr;
    other.detailCount = 0;
    other.capacity = 0;
}

// Оператор присваивания с перемещением
AssemblyInstruction& AssemblyInstruction::operator=(AssemblyInstruction&& other) noexcept {
    if (this != &other) {
        delete[] details;
        details = other.details;
        detailCount = other.detailCount;
        capacity = other.capacity;
        other.details = nullptr;
        other.detailCount = 0;
        other.capacity = 0;
    }
    return *this;
}

// Деструктор
AssemblyInstruction::~AssemblyInstruction() {
    if (details != nullptr)
        delete[] details;
}

// Метод для добавления новой детали
AssemblyInstruction& AssemblyInstruction::operator+=(const Detail& detail) {
    if (detailCount == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    details[detailCount++] = detail;
    return *this;
}

// Оператор доступа по индексу
Detail& AssemblyInstruction::operator[](int index) {
    if (index >= 0 && index < detailCount) {
        return details[index];
    }
    throw std::out_of_range("Index out of range");
}

// Метод для удаления детали
// void AssemblyInstruction::removeDetail(int index) {
//     if (index < 0 || index >= detailCount) {
//         throw std::out_of_range("Index out of range");
//     }
    
//     // Удаление детали
//     for (int i = index; i < detailCount - 1; ++i) {
//         details[i] = std::move(details[i + 1]);
//     }
//     --detailCount;
// }
void AssemblyInstruction::removeDetail(int index) {
    if (index < 0 || index >= detailCount) {
        throw std::out_of_range("Index out of range");
    }

    // Проверяем все детали на наличие зависимостей
    for (int i = 0; i < detailCount; i++) {
        if (i != index) {
            auto requiredDetails = details[i].getRequiredDetails();
            // Проверяем, требуется ли удаляемая деталь для текущей детали
            if (std::find(requiredDetails.begin(), requiredDetails.end(), index) != requiredDetails.end()) {
                throw std::runtime_error("Cannot remove detail: it is required for assembly of other details");
            }
        }
    }
    
    // Удаление детали
    for (int i = index; i < detailCount - 1; ++i) {
        details[i] = std::move(details[i + 1]);
    }
    --detailCount;

    // После удаления нужно обновить индексы в requiredDetails для оставшихся деталей
    // Создаем новые детали с обновленными индексами
    for (int i = 0; i < detailCount; ++i) {
        auto oldDetails = details[i];
        Detail newDetail(oldDetails.getName(), oldDetails.getType(), {}, oldDetails.getAssemblyInstructions());
        
        // Копируем требуемые детали с обновленными индексами
        for (int reqDetail : oldDetails.getRequiredDetails()) {
            if (reqDetail > index) {
                newDetail.addRequiredDetail(reqDetail - 1);
            } else if (reqDetail < index) {
                newDetail.addRequiredDetail(reqDetail);
            }
        }
        
        details[i] = newDetail;
    }
}

// Метод для получения количества деталей
int AssemblyInstruction::getDetailCount() const {
    return detailCount;
}

// Вспомогательный метод для проверки циклов при сборке
bool AssemblyInstruction::hasCycle(int detailIndex, std::vector<bool>& visited, std::vector<bool>& recursionStack) const {
    if (!visited[detailIndex]) {
        visited[detailIndex] = true;
        recursionStack[detailIndex] = true;

        for (int reqDetail : details[detailIndex].getRequiredDetails()) {
            if (!visited[reqDetail] && hasCycle(reqDetail, visited, recursionStack)) {
                return true;
            }
            else if (recursionStack[reqDetail]) {
                return true;
            }
        }
    }
    recursionStack[detailIndex] = false;
    return false;
}

// Проверка возможности сборки финальной детали
bool AssemblyInstruction::canAssembleFinalDetail() const {
    if (detailCount == 0) return false;

    // Проверяем наличие циклов для каждой детали
    std::vector<bool> visited(detailCount);
    std::vector<bool> recursionStack(detailCount);

    // Проверка на циклы
    for (int i = 0; i < detailCount; ++i) {
        if (hasCycle(i, visited, recursionStack)) {
            return false;
        }
    }

    // Проверяем наличие всех необходимых деталей
    for (int i = 0; i < detailCount; ++i) {
        if (details[i].getType() == DetailType::Final) {
            // Для финальной детали проверяем наличие всех требуемых деталей
            for (int reqDetail : details[i].getRequiredDetails()) {
                if (reqDetail >= detailCount) {
                    return false;
                }
            }
            return true; // Нашли финальную деталь и все требуемые детали существуют
        }
    }

    return false; // Не нашли финальную деталь
}

// Получение отсортированного списка исходных деталей
std::vector<std::string> AssemblyInstruction::getOriginalDetailsSorted() const {
    std::vector<std::string> originalDetails;
    
    // Собираем все исходные детали
    for (int i = 0; i < detailCount; ++i) {
        if (details[i].getType() == DetailType::Original) {
            originalDetails.push_back(details[i].getName());
        }
    }
    
    // Сортируем по алфавиту
    std::sort(originalDetails.begin(), originalDetails.end());
    
    return originalDetails;
}

// Получение вектора деталей в порядке их сборки
std::vector<Detail> AssemblyInstruction::getAssemblySequence() const {
    std::vector<Detail> sequence;
    if (detailCount == 0) return sequence;

    // Создаем множество необработанных деталей
    std::vector<bool> processed(detailCount, false);
    
    while (sequence.size() < detailCount) {
        bool foundNext = false;
        
        // Ищем следующую деталь для добавления
        for (int i = 0; i < detailCount; ++i) {
            if (processed[i]) continue;
            
            // Получаем требуемые детали для текущей детали
            auto requiredDetails = details[i].getRequiredDetails();
            
            // Проверяем, все ли требуемые детали уже в последовательности
            bool canAdd = true;
            for (int reqDetail : requiredDetails) {
                bool found = false;
                // Ищем требуемую деталь среди уже добавленных
                for (size_t j = 0; j < sequence.size(); ++j) {
                    if (static_cast<int>(j) == reqDetail) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    canAdd = false;
                    break;
                }
            }
            
            // Если все требуемые детали уже в последовательности,
            // добавляем текущую деталь
            if (canAdd) {
                sequence.push_back(details[i]);
                processed[i] = true;
                foundNext = true;
                break;
            }
        }
        
        // Если не удалось найти следующую деталь, значит есть циклическая зависимость
        if (!foundNext) {
            // Возвращаем пустой вектор в случае невозможности построить корректную последовательность
            return std::vector<Detail>();
        }
    }
    
    // Проверяем корректность полученной последовательности
    if (!isValidSequence(sequence)) {
        return std::vector<Detail>();
    }
    
    return sequence;
}

// Вспомогательный метод для проверки корректности последовательности сборки
bool AssemblyInstruction::isValidSequence(const std::vector<Detail>& sequence) const {
    // Для каждой детали проверяем, что все её зависимости идут до неё
    for (size_t i = 0; i < sequence.size(); ++i) {
        for (int reqDetail : sequence[i].getRequiredDetails()) {
            bool found = false;
            // Ищем требуемую деталь среди предыдущих деталей
            for (size_t j = 0; j < i; ++j) {
                if (static_cast<int>(j) == reqDetail) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
    }
    return true;
}

// Метод для получения пошаговой инструкции сборки
std::string AssemblyInstruction::getAssemblyInstructions() const {
    if (!canAssembleFinalDetail()) {
        return "Cannot generate assembly instructions: invalid assembly structure";
    }

    auto sequence = getAssemblySequence();
    if (sequence.empty()) {
        return "Cannot generate assembly instructions: invalid assembly sequence";
    }

    std::stringstream result;
    std::unordered_map<std::string, int> usageCount; // Для подсчёта использования деталей
    std::unordered_set<std::string> processedDetails; // Для отслеживания уже собранных деталей

    for (size_t i = 0; i < sequence.size(); ++i) {
        const auto& detail = sequence[i];
        
        // Пропускаем исходные детали
        if (detail.getType() == DetailType::Original) {
            continue;
        }

        // Если деталь уже была собрана, пропускаем её
        if (processedDetails.find(detail.getName()) != processedDetails.end()) {
            continue;
        }

        result << "Step " << processedDetails.size() + 1 << ": Assemble " << detail.getName();
        
        // Получаем требуемые детали для текущей сборки
        auto requiredDetails = detail.getUniqueRequiredDetails();
        if (!requiredDetails.empty()) {
            result << " using ";
            bool first = true;
            
            // Проходим по всем требуемым деталям
            for (const auto& [detailIndex, count] : requiredDetails) {
                if (!first) {
                    result << ", ";
                }
                first = false;

                const auto& reqDetail = details[detailIndex];
                result << reqDetail.getName();
                
                // Если деталь используется больше одного раза, добавляем количество
                if (count > 1) {
                    result << " (x" << count << ")";
                }
                
                usageCount[reqDetail.getName()]++;
            }
        }

        // Добавляем инструкции по сборке, если они есть
        if (!detail.getAssemblyInstructions().empty()) {
            result << "\nInstructions: " << detail.getAssemblyInstructions();
        }

        result << "\n";
        processedDetails.insert(detail.getName());
    }

    return result.str();
}


// Оператор вывода
std::ostream& operator<<(std::ostream& os, const AssemblyInstruction& instruction) {
    os << "Assembly Instruction:\n";
    for (int i = 0; i < instruction.detailCount; ++i) {
        os << instruction.details[i] << "\n\n";
    }
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, AssemblyInstruction& instruction) {
    instruction = AssemblyInstruction(); // Сбрасываем текущее состояние
    std::string line;

    while (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string name;
        int type;
        iss >> name >> type;

        Detail detail(name);
        detail.setType(static_cast<DetailType> (type));
        int requiredDetail;
        while (iss >> requiredDetail) {
            detail.addRequiredDetail(requiredDetail);
        }

        instruction += detail;
    }

    return is;
}