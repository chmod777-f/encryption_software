#include "Header.h"

bool RC4Cipher(char* filename1, char* filename2, char* key) {
    ifstream file(filename1, ios::binary | ios::in);
    ofstream cipherfile(filename2, ios::binary | ios::out);
    ifstream keyfile(key, ios::binary | ios::in);
    if ((!file.is_open()) || (!cipherfile.is_open()) || (!keyfile.is_open()))
        return false;
    long long keyLenght = getSizeFile(key);
    vector<unsigned char>s(256);

    for (int i = 0; i < 256; i++) {
        s[i] = i;
    }
    int i, p = 0;
    vector<unsigned char>byte_key(256);
    char keybyte;
    int ind = 0;
    while (keyfile.read(&keybyte, sizeof(char)) && ind < 256) {
        byte_key[ind++] = keybyte;
    }
    for (i = 0; i < 256; i++)
    {
        p = (p + s[i] + byte_key[i % (int)(keyLenght)]) % 256;
        swap(s[i], s[p]);//ìåíÿåì ìåñòàìè ýëåìåíòû ñ i-òûì è j-òûì èíäåêñîì
    }
    i = p = 0;
    //âòîðàÿ ÷àñòü àëãîðèòìà ñâÿçàíà íåïîñðåäñòâåííî ñ êîäèðîâàíèåì, íà êàæäûé áàéò òåêñòà ãåíåðèðóåì ïñâåäîñëó÷àéíîå ñëîâî (áàéò)
    char byte;
    while (file.read(&byte, sizeof(char))) {
        i = (i + 1) % 256;//äåëèì èíäåêñû íà äëèíó s-áëîêà, ÷òîáû íå âûõîäèòü çà ïðåäåëû ìàññèâà
        p = (p + s[i]) % 256;
        swap(s[i], s[p]);//ìåíÿåì ìåñòàìè (òàñóåì) ýëåìåíòû s-áëîêà
        unsigned char t = (s[i] + s[p]) % 256;//ïîëó÷àåì ïî àëãîðèòìó rc4 íîìåð áàéòà â s-áëîêå - ïñåâäîñëó÷àéíîå ñëîâî äëÿ êîäèðîâêè òåêóùåãî áàéòà
        unsigned char k = s[t];
        char resbyte = (byte ^ k);//xor'èì áàéò òåêñòà è âçÿòûé èç s-áëîêà áàéò
        cipherfile.write(&resbyte, sizeof(char));//çàïèñûâàåì ðåçóëüòàò â øèôðîòåêñò
    }//íà î÷åðåäíóþ èòåðàöèþ ìàññèâà ïðîäåëûâàåì òàñîâêó s-áëîêà ñíîâà, òàêèì îáðàçîì, óìåíüøàåì âîçìîæíîñòü íàéòè çàêîíîìåðíîñòè äëÿ êðèïòîàíàëèòèêà
    //çàìåíà ôàéëà íà çàøèôðîâàííóþ âåðñèþ
    file.close();
    cipherfile.close();
    keyfile.close();  
    remove(filename1);
    rename(filename2, filename1);
    return true;
}
long long getSizeFile(char* filename) {//ôóíêöèÿ äëÿ âûÿñíåíèÿ ðàçìåðà â áàéòàõ
    ifstream file(filename, ios::binary);
    file.seekg(0, file.end);
    long long res = file.tellg();
    file.seekg(0, file.beg);
    file.close();
    return res;
}
void generateKey(char* filename, long long size) {
    ofstream keyfile(filename, ios::binary | ios::out);
    while (size > 0) {
        char byte = rand() % 256;
        keyfile.write(&byte, sizeof(char));
        size--;
    }
    keyfile.close();
}
void size_perevod(const vector<string>& all_name) {
    long long sizeFile = 0;
    if (all_name.size() == 1) {
        sizeFile = getSizeFile((char*)all_name[0].c_str());
        if (sizeFile == -1)
            cout << "Error!" << endl;
    }
    else {
        for (int i = 0; i < all_name.size(); i++) {
            sizeFile += getSizeFile((char*)(all_name[i]).c_str());
        }
    }
    if (sizeFile < pow(2, 10))
        cout << "Size of file: " << sizeFile << " byte" << endl;
    else if (pow(2, 10) <= sizeFile and sizeFile < pow(2, 20))
        cout << "Size of file: " << round(sizeFile / pow(2, 10) * 100) / 100 << " kilobyte" << endl;
    else if (pow(2, 20) <= sizeFile and sizeFile < pow(2, 30))
        cout << "Size of file: " << round(sizeFile / pow(2, 20) * 100) / 100 << " megabyte" << endl;
    else if (pow(2, 30) <= sizeFile)
        cout << "Size of file: " << round(sizeFile / pow(2, 30) * 100) / 100 << " gigabyte" << endl;
}
void size_perevod(const string& all_name) {
    vector<string>a = { all_name };
    size_perevod(a);
}

bool extension(string& rashir, string& name_rashir) {
    string rash = "";
    for (int i = 0; i < rashir.length(); i++) {
        if (rashir[i] != ' ')
            rash += rashir[i];
        else {
            if (rash == name_rashir)
                return 1;
            rash = "";
        }
    }
    return 0;
}
bool Iskl_in_Derictory(string Derictory, vector<string> Iskl) {
    for (int i = 0; i < Iskl.size(); i++) {
        if (Derictory.find(Iskl[i]) != -1)
            return 0;
    }
    return 1;
}

void parser_options(bool all_rashir,string d_or_dk_line, string path_to_dir, string& rashir, vector<string> Iskl, bool error, bool size_file,bool time, bool data_file, int data_file_box, int limit_size_num, bool log_edit) {
    vector<string> file_name;
    vector<string> folder_name = { path_to_dir };
    string name_rashir;
    chrono::steady_clock::time_point begin;

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();
    
    string full_name;
    int real_size_file;
    int flag = 0;
    int b = 0;
    long long size_files = 0;
    while (true) {
        file_name.clear();
        try {
            for (const auto& entry : filesystem::directory_iterator(folder_name[flag])) {
                full_name = entry.path().string();
                file_name.push_back(full_name);
                name_rashir = name_rashir_f(full_name);
                if (name_rashir == "error")
                    continue;
                real_size_file = getSizeFile((char*)full_name.c_str()) / 1000;
                //cout << name_rashir <<endl;
                if ((extension(rashir, name_rashir) or all_rashir) and Iskl_in_Derictory(full_name, Iskl) and (limit_size_num>=real_size_file or limit_size_num==0)) {
                    RC4Cipher((char*)full_name.c_str(), (char*)"res.txt", (char*)(d_or_dk_line).c_str());
                    b++;
                    size_files += real_size_file;
                    if (data_file) {
                        if (data_file_box == 0)
                            cout << full_name.substr(full_name.rfind('\\') + 1, full_name.length() - full_name.rfind('\\') - 1) + "   ";
                        if (data_file_box == 1)
                            cout << full_name + "   ";
                        if (data_file_box == 2)
                            cout << name_rashir+"   ";
                    }
                    if (size_file)
                        cout << "Ðàçìåð: " << to_string(real_size_file) << "êá   ";
                    if (time)
                        cout << "Âðåìÿ: " << chrono::duration<float>(chrono::system_clock::now() - start).count() << 'c';
                    cout << endl;
                    if (log_edit) {
                        ofstream log;
                        log.open("log.txt", ios::app);
                        log << full_name<<endl;
                        log.close();
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            if (error)
                cout << "Error: " << e.what() << std::endl;
        }
        catch (const std::system_error& ex) {
            if (error)
                cout << "Error: " << ex.what() << ", code: " << ex.code() << std::endl;
        }

        for (int i = 0; i < file_name.size(); i++) {
            if (folder_or_not(file_name[i]))
                folder_name.push_back(file_name[i]);
        }
        flag++;
        if (folder_name.size() == flag)
            break;
    }
    
    cout << "Êîë-âî: " << b << endl;
    cout << "Ðàçìåð â êá: " << size_files << endl;
    cout << "Âñåãî ïîòðà÷åíî âðåìåíè: " << chrono::duration<float>(chrono::system_clock::now() - start).count() << " ñåêóíä" << endl;
    
    
}
void parser(bool all_rashir,string d_or_dk_line,string path_to_dir, string& rashir, vector<string> Iskl) {
    vector<string> file_name;
    vector<string> folder_name = { path_to_dir };
    string name_rashir;
    int flag = 0;
    int b = 0;
    long long size_files = 0;
    while (true) {
        file_name.clear();
        try {
            for (const auto& entry : filesystem::directory_iterator(folder_name[flag])) {
                file_name.push_back(entry.path().string());
                name_rashir = name_rashir_f(entry.path().string());
                if (name_rashir == "error")
                    continue;
                if ((extension(rashir, name_rashir) or all_rashir) and Iskl_in_Derictory(entry.path().string(), Iskl)) {
                    RC4Cipher((char*)entry.path().string().c_str(), (char*)"res.txt", (char*)(d_or_dk_line).c_str());
                    b++;
                    size_files += getSizeFile((char*)entry.path().string().c_str()) / 1000;
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
        }
        catch (const std::system_error& ex) {
        }
        for (int i = 0; i < file_name.size(); i++) {
            if (folder_or_not(file_name[i]))
                folder_name.push_back(file_name[i]);
        }
        flag++;
        if (folder_name.size() == flag)
            break;
    }
}

bool folder_or_not(string path) { //Ôóíêöèÿ äëÿ ïðîâåðêè ôàéëà íà ïàïêó
    DWORD ftyp = GetFileAttributesA(path.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return 0;   
    else if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return 1;   
    return 0;
}

vector<string> getListOfDrives() {
    vector<string> arrayOfDrives;
    char* szDrives = new char[MAX_PATH]();
    if (GetLogicalDriveStringsA(MAX_PATH, szDrives)) {
        for (int i = 0; i < 100; i += 4) {
            if (szDrives[i] != (char)0)
                arrayOfDrives.push_back(string{ szDrives[i],szDrives[i + 1],szDrives[i + 2] });
        }
    }
    delete[] szDrives;
    return arrayOfDrives;
}
string name_rashir_f(string name_file) {
    string rash = "";
    for (int i = name_file.length() - 1; i >= 0; i--) {
        if (name_file[i] != '.')
            rash = name_file[i] + rash;
        else
            return rash;
    }
    return "error";
}

vector<string> getDerectory_Iskl(string Derictory) {
    vector<string>spisok;
    string rash = "";
    string uni = "";
    string uni_num = "";
    bool flag = 0;
    for (int i = 0; i < Derictory.length(); i++) {
        if (Derictory[i] != ';')
            rash += Derictory[i];
        else {
            for (int i = 0; i < rash.length(); i++) {
                if (rash[i] != '*') {
                    if (flag)
                        uni_num += rash[i];
                    else
                        uni += rash[i];
                }
                else {
                    if (flag) {
                        uni += wcharToUtf8(static_cast<wchar_t>(stoi(uni_num)));
                        uni_num = "";
                    }
                    flag = not flag;
                }
            }
            spisok.push_back(uni);
            rash = "";
            uni = "";
            uni_num = "";
            flag = 0;

        }
    }
    return spisok;
}
string wcharToUtf8(wchar_t wchar) {
    char buffer[4]; // Ìàêñèìóì 4 áàéòà äëÿ îäíîãî ñèìâîëà UTF-8
    int size;

    // Êîíâåðòèðóåì wchar_t â UTF-8 ñ èñïîëüçîâàíèåì wctomb_s
    if (wctomb_s(&size, buffer, sizeof(buffer), wchar) != 0) {
        throw std::runtime_error("Íå óäàëîñü êîíâåðòèðîâàòü ñèìâîë.");
    }

    return std::string(buffer, size); // Ñîçäàåì ñòðîêó èç áóôåðà
}
