# crawler
## 說明
* 此程式非本人原創，參考[Curl_Example Sources](https://curl.se/libcurl/c/example.html)的程式碼，理解後補上註解並修改。
* 此程式碼之版權屬於Daniel Stenberg大神，再此附上[版權說明](https://curl.se/docs/copyright.html)
## 環境設置
* 因為crul非標準函式庫需使用以下指令安裝:
* ```sudo apt-get install libcurl4-gnutls-dev```
![apt-get install libcurl4-gnutls-dev](https://user-images.githubusercontent.com/62127656/122444468-2920da00-cfd3-11eb-9fa9-257e19198719.PNG)

* 利用10-at-a-time.c進行測試

![10-at-a-time](https://user-images.githubusercontent.com/62127656/122444458-245c2600-cfd3-11eb-83c1-8d938b75758e.PNG)
## 程式說明
* 使用libcurl的大概流程
   1. 調用curl_global_init()初始化libcurl
   2. 調用curl_easy_init()函數得到easy interface型指針
   3. 調用curl_easy_setopt()設置傳輸選項
   4. 根據curl_easy_setopt()設置的傳輸選項，實現回調函數以完成用戶特定任務
   5. 調用curl_easy_perform()函數完成傳輸任務
   6. 調用curl_easy_cleanup()釋放記憶體

## 參考資料
* [C 語言 Libcurl 函式庫基本使用](http://xshadowwolfx.blogspot.com/2012/12/c-libcurl.html)
* [Installing curl.h library [duplicate]](https://askubuntu.com/questions/78183/installing-curl-h-library)
* 
