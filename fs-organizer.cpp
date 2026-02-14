#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

fs::path uniquePath(const fs::path& destPath)
{
    if(!fs::exists(destPath))
    {
        return destPath;
    }
    fs::path parent = destPath.parent_path();
    auto stem = destPath.stem().string();
    auto ext = destPath.extension().string();

    int counter = 1;
    fs::path newPath;

    do
    {
        newPath = parent / (stem + "(" + to_string(counter) + ")" + ext);
        counter++;
    } while (fs::exists(newPath));
    
    return newPath;
}

unsigned long long hashing(const fs::path& filePath)
{
    ifstream file(filePath, ios::binary);

    if (!file)
    {return 0;}

    unsigned long long hash = 0;
    char byte;

    while (file.read(&byte, 1))
    {
        hash += (unsigned char)byte;
    }

    return hash;
}

int main()
{
    string folderPath;
    unsigned long long totalSaved = 0;
    
    unordered_set <string> imageExtensions = 
    {".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff", ".webp"};
    unordered_set<string> videoExtensions =
    {".mp4", ".avi", ".mkv", ".mov", ".flv", ".wmv", ".webm"};
    unordered_set<string> documentExtensions =
    {".pdf", ".doc", ".docx", ".txt", ".ppt", ".pptx", ".xls", ".xlsx"};
    unordered_set<string> musicExtensions =
    {".mp3", ".wav", ".flac", ".aac", ".ogg", ".wma"};
    unordered_set<string> archiveExtensions =
    {".zip", ".rar", ".7z", ".tar", ".gz"};

    while (true)
    {
        cout << "Enter A Folder Path: ";
        getline (cin, folderPath);

        if (fs::exists(folderPath) && fs::is_directory(folderPath))
        {
            break;
        }else
        {
            cout << "Invalid Folder Path, Try Again!" << endl;
        }
    }

    unordered_map <uintmax_t, vector<fs::path>> filesBySize;
    for (const auto& entry : fs::recursive_directory_iterator(folderPath))
    {
        if (!fs::is_regular_file(entry))
        {
            continue;
        }

        uintmax_t size = fs::file_size(entry);
        filesBySize[size].push_back(entry.path());
    }

    for (const auto& [size, files] : filesBySize)
    {
        if (files.size() < 2)
        continue;

        unordered_map <unsigned long long, vector<fs::path>> filesByHash;

        for (auto& file : files)
        {
            unsigned long long h = hashing(file);
            filesByHash[h].push_back(file);
        }

        for (auto& [h, dupFiles] : filesByHash)
        {
            if (dupFiles.size() > 1)
            {
                cout << "Duplicate Group (Size: " << size << " Bytes):" << endl;
                for (size_t i = 0; i < dupFiles.size(); i++)
                {
                    cout << "  [" << i+1 << "] " << dupFiles[i] << endl;
                }
                for (size_t i = 1; i < dupFiles.size(); i++)
                {
                    cout << "Delete " << dupFiles[i] << " ? (y/n): ";
                    char answer;
                    cin >> answer;
                    if (answer == 'y' || answer == 'Y')
                    {
                        uintmax_t fileSize = fs::file_size(dupFiles[i]);
                        fs::remove(dupFiles[i]);
                        totalSaved += fileSize;
                        cout << "Deleted!" << endl;
                    }
                }
            }
        }
    }

    for (const auto& entry : fs::recursive_directory_iterator(folderPath))
    {
        auto ext = entry.path().extension().string();
        transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        auto fileName = entry.path().filename().string();
        auto filePath = entry.path().string();
        string fileDest;

        if (imageExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Images");
            fileDest = folderPath + "/Images/" + fileName;
            fs::path finalDest = uniquePath(fileDest);
            fs::rename(filePath, finalDest);
        }else if (videoExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Videos");
            fileDest = folderPath + "/Videos/" + fileName;
            fs::path finalDest = uniquePath(fileDest);
            fs::rename(filePath, finalDest);

        }else if (documentExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Documents");
            fileDest = folderPath + "/Documents/" + fileName;
            fs::path finalDest = uniquePath(fileDest);
            fs::rename(filePath, finalDest);

        }else if (archiveExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Archives");
            fileDest = folderPath + "/Archives/" + fileName;
            fs::path finalDest = uniquePath(fileDest);
            fs::rename(filePath, finalDest);

        }else if (musicExtensions.count(ext))
        {
            fs::create_directories(folderPath + "/Music");
            fileDest = folderPath + "/Music/" + fileName;
            fs::path finalDest = uniquePath(fileDest);
            fs::rename(filePath, finalDest);
        }
    }

    cout << "\nDone! Folder Cleaning Completed!" << endl;
    cout << "Total Space Saved: " << totalSaved / (1024*1024) << " MB" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press Enter To Exit.";
    cin.get();
    return 0;
}