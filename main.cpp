/*
Program for Linux
*/
/* ファイル操作プログラムサンプル */
#include <iostream>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

constexpr uint32_t PATH_MAX{256};

std::string GetExecutableFolderPath(void)
{
    char path[PATH_MAX + 1]{};
    const size_t LINKSIZE{100};
    char link[LINKSIZE];
    std::string result_path{"\0"};

    // 実行中のプロセスのシンボリックリンク
    snprintf(link, LINKSIZE, "/proc/%d/exe", getpid() );

    // ファイルパスを得る
    ssize_t buf_size{readlink( link, path, PATH_MAX)};

    
    if (buf_size < 0)
    {
        printf("E readlink Error.");
        
    }
    else
    {
        std::string path_str_tmp{path};
        size_t lastSeparater = path_str_tmp.find_last_of("\\/");
        uint32_t pos = path_str_tmp.rfind("\/");
        result_path = path_str_tmp.erase(pos);
        printf("D [get path] %s\n", result_path.c_str());
    }

    return result_path;
}

void ShowContents(std::string FolderName)
{
    printf("showcontents.\n");
    try
    {
        std::filesystem::path fsyspath{FolderName};
        bool exists{std::filesystem::exists(fsyspath)};
        bool isdirectory{std::filesystem::is_directory(fsyspath)};
        printf("exists = %s, isdirectory = %s\n", exists ? "TRUE" : "FALSE", isdirectory ? "TRUE" : "FALSE");

        if (std::filesystem::exists(FolderName) && std::filesystem::is_directory(FolderName))
        {
            printf("filesystem\n");
            for (const auto& entry : std::filesystem::directory_iterator(FolderName))
            {
                std::cout << entry.path().filename() << "\n";
            }
        }
        else
        {
            std::cerr << "Folder does not exits or is not a directory. " << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& fex)
    {
        std::cerr << "FileSystem error " << fex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error Showing file contents: " << ex.what() << std::endl;
    }
}

int main(void)
{
    std::string folderpath{GetExecutableFolderPath()};
    printf("folderpath: %s\n", folderpath.c_str());
    ShowContents(folderpath);
    return 0;
}
