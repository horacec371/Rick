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