#include "Header.h"
#include "config_file.h"

int main(int argc, char** argv) {
    CFG::SetDebugLevel(0);
    setlocale(LC_ALL, "RU");
    //MAIN
    int d_or_dk;
    string d_or_dk_line;
    bool all_rashir;
    string rashir;
    bool all_derrictory;
    string Derictory;
    string Iskl;
    bool log_edit;
    int algoritm;
    int key_lenght;
    bool limit_size;
    int limit_size_num;
    int limit_size_unit;
    //CMD
    bool cmd_on;
    bool error;
    bool size_file;
    bool time;
    bool data_file;
    int data_file_box;
    vector<string>cfg_name = { "d_or_dk","d_or_dk_line","all_rashir", "rashir","all_derrictory","Derictory","Iskl" ,"log_edit" ,"algoritm" ,"key_lenght",
        "limit_size","limit_size_num", "limit_size_unit", "cmd_on", "error", "size_file","time", "data_file", "data_file_box" };
    ifstream f_out("settings.cfg");
    CFG::ReadFile(f_out, cfg_name, d_or_dk, d_or_dk_line, all_rashir, rashir, all_derrictory, Derictory, Iskl, log_edit, algoritm, key_lenght,
        limit_size, limit_size_num, limit_size_unit, cmd_on, error, size_file, time, data_file, data_file_box);
    if(!limit_size)
        limit_size_num = 0;
    else {
        switch (limit_size_unit)
        {
        case 0:limit_size_num /= 1024; break;
        case 2:limit_size_num *= 1024; break;
        case 3:limit_size_num *= 1024*1024; break;
        default:break;
        }
    }

    rashir += " ";
    Derictory = Derictory.substr(1, Derictory.length());
    Iskl = Iskl.substr(1, Iskl.length());
    for (int i = 0; i < Derictory.length(); i++) {
        if (Derictory[i] == '\\')
            Derictory.replace(i, 2, "\\");
    }
    for (int i = 0; i < Iskl.length(); i++) {
        if (Iskl[i] == '\\')
            Iskl.replace(i, 2, "\\");
    }


    if (log_edit) {
        ofstream log;
        log.open("log.txt", ios::out);
        log.close();
    }

    if (d_or_dk == 0)
        generateKey((char*)d_or_dk_line.c_str(), key_lenght);

    vector<string>Iskl_spisok = getDerectory_Iskl(Iskl);
    if (all_derrictory) {
        vector<string> drives = getListOfDrives();
        if (cmd_on or log_edit) {
            for (int i = 0; i < drives.size(); i++) {
                parser_options(all_rashir,d_or_dk_line,drives[i], rashir, Iskl_spisok, error, size_file, time, data_file, data_file_box, limit_size_num, log_edit);
            }
        }
        else {
            for (int i = 0; i < drives.size(); i++) {
                parser(all_rashir,d_or_dk_line,drives[i], rashir, Iskl_spisok);
            }
        }
    }
    else {
        vector<string>Derictory_spisok = getDerectory_Iskl(Derictory);
        if (cmd_on or log_edit) {
            for (int i = 0; i < Derictory_spisok.size(); i++) {
                parser_options(all_rashir,d_or_dk_line,Derictory_spisok[i], rashir, Iskl_spisok, error, size_file,time, data_file, data_file_box, limit_size_num, log_edit);
            }
        }
        else {
            for (int i = 0; i < Derictory_spisok.size(); i++) {
                parser(all_rashir,d_or_dk_line,Derictory_spisok[i], rashir, Iskl_spisok);
            }
        }
        
    }

    system("pause");
    return 0;
}