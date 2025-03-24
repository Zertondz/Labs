#ifndef DIALO_H_INCLUDED
#define DIALO_H_INCLUDED

int entering_in_a_table(Table * table);
int deleting_all_items_by_key(Table *table);
int deleting_a_version_by_key(Table *table);
int search_by_key(Table * table);
int search_by_key_and_release(Table *table);
int output_to_a_file(Table * table);
int input_from_a_file(Table ** table);
int initialization(Table ** table);
int input_from_a_file_initial(Table ** table);
#endif // DIALO_H_INCLUDED
