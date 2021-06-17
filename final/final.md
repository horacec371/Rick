# 期末專案:爬蟲
## 說明
* 此程式非本人原創，參考[Curl_Example Sources](https://curl.se/libcurl/c/example.html)的程式碼，理解後補上註解並修改。
* 此程式碼之版權屬於Daniel Stenberg大神，再此附上[版權說明](https://curl.se/docs/copyright.html)
## 環境設置
* 因為crul非標準函式庫需使用以下指令安裝:
* ```sudo apt-get install libcurl4-gnutls-dev```
![apt-get install libcurl4-gnutls-dev](https://user-images.githubusercontent.com/62127656/122444468-2920da00-cfd3-11eb-9fa9-257e19198719.PNG)

* 利用[10-at-a-time.c](https://curl.se/libcurl/c/10-at-a-time.html)進行測試

![10-at-a-time](https://user-images.githubusercontent.com/62127656/122444458-245c2600-cfd3-11eb-83c1-8d938b75758e.PNG)
## 程式說明
* 使用libcurl的大概流程
   1. 調用curl_easy_init()函數得到easy interface型指針
   2. 調用curl_easy_setopt()設置傳輸選項
   3. 根據curl_easy_setopt()設置的傳輸選項，實現回調函數以完成用戶特定任務
   4. 調用curl_easy_perform()函數完成傳輸任務
   5. 調用curl_easy_cleanup()釋放記憶體
* 程式簡介
   * 簡易的取得html並存於其他檔案中
* [程式碼](https://github.com/cycyucheng1010/sp109b/blob/main/final/curl.c)
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

//定義一個寫入檔案的函式 
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
 
int main(void)
{
  CURL *curl_handle;
  static const char *headerfilename = "head.out";//一個檔案叫head.out印出header
  FILE *headerfile;
  static const char *bodyfilename = "body.out";//另一檔案叫body.out印出html
  FILE *bodyfile;
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* 初始化整個程式，curl_easy_init這個函數會自動調整，但最好可以使用curl_global_init */
  curl_handle = curl_easy_init();
 
  /* 設定要取得的網頁，這邊使用的是國立金門大學的官網 */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://www.nqu.edu.tw/cht/index.php?");
 
  /* no progress meter please */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
  /* 將資料傳送到前面的寫入函數中  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  /* 建立一個名叫head的2進位檔案*/
  headerfile = fopen(headerfilename, "wb");
  if(!headerfile) {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
 
  /* 建立一個名叫body的2進位檔案 */
  bodyfile = fopen(bodyfilename, "wb");
  if(!bodyfile) {
    curl_easy_cleanup(curl_handle);
    fclose(headerfile);
    return -1;
  }
 
  /* 將header寫入head.out */
  curl_easy_setopt(curl_handle, CURLOPT_HEADERDATA, headerfile);
 
  /* 將html寫入body.out */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
 
  /* 執行 */
  curl_easy_perform(curl_handle);
 
  /* 關閉head.out檔 */
  fclose(headerfile);
 
  /* 關閉body.out檔 */
  fclose(bodyfile);
 
  /* 關閉爬蟲 */
  curl_easy_cleanup(curl_handle);
 
  return 0;
```
## 結果
* [head.out](https://github.com/cycyucheng1010/sp109b/blob/main/final/head.out)

![image](https://user-images.githubusercontent.com/62127656/122452051-6b4e1980-cfdb-11eb-8b9e-d10516d77738.png)

* [body.out](https://github.com/cycyucheng1010/sp109b/blob/main/final/body.out)

![image](https://user-images.githubusercontent.com/62127656/122451995-56718600-cfdb-11eb-98b0-864e66f657da.png)

## 參考資料
* [C 語言 Libcurl 函式庫基本使用](http://xshadowwolfx.blogspot.com/2012/12/c-libcurl.html)
* [Installing curl.h library [duplicate]](https://askubuntu.com/questions/78183/installing-curl-h-library)
* [libcurl - small example snippets](https://curl.se/libcurl/c/example.html)
* [fopen中w w+ wb区别：](https://blog.csdn.net/guyue6670/article/details/6681037)
* [在Linux用C/C++編寫使用libcurl的程式](https://vrabe.tw/blog/using-libcurl-in-c-or-cpp-in-linux/)
* [sepheaders.c](https://curl.se/libcurl/c/sepheaders.html)
