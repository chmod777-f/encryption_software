#ifndef Header_h
#define Header_h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <filesystem>
#include<map>
#include <chrono>
using namespace std;


long long getSizeFile(char* filename);
bool RC4Cipher(char* filename1, char* filename2, char* key);
void generateKey(char* filename, long long size);
void size_perevod(const vector<string>& all_name);
void size_perevod(const string& all_name);
bool folder_or_not(string path);
void parser(bool all_rashir, string d_or_dk_line, string path_to_dir, string& rashir, vector<string> Iskl);
void parser_options(bool all_rashir, string d_or_dk_line, string path_to_dir, string& rashir, vector<string> Iskl, bool error, bool size_file, bool time, bool data_file, int data_file_box, int limit_size_num, bool log_edit);
bool extension(string& rashir, string& name_rashir);
vector<string> getListOfDrives();
string name_rashir_f(string name_file);
string wcharToUtf8(wchar_t wchar);
vector<string> getDerectory_Iskl(string Derictory);
bool Iskl_in_Derictory(string Derictory, vector<string> Iskl);
#endif




