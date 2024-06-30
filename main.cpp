/*
Program for Linux
*/

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

    // ファイルパスが得る
    ssize_t buf_size{readlink( link, path, PATH_MAX)};

    
    if (buf_size < 0)
    {
        printf("E readlink Error.");
        
    }
    else
    {
        std::string path_str_tmp{path};
        result_path = path_str_tmp;
        result_path += '\0';
        printf("D [get path] %s\n", result_path.c_str());
    }

    return result_path;
}


int main(void)
{
    GetExecutableFolderPath();
    return 0;
}