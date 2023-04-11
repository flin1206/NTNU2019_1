#include <stdio.h>
#include <curl/curl.h>
#include <assert.h>
 
int main(void)
{
    CURL *curl;
    CURLcode res;
 
    curl = curl_easy_init();
  
    if(curl) 
    {
        curl_easy_setopt( curl, CURLOPT_URL, "https://data.taipei/api/frontstage/tpeod/dataset/resource.download?rid=2979c431-7a32-4067-9af2-e716cd825c4b" );
        
        FILE *pFile = fopen( "123.txt", "w" );
        assert( pFile );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, pFile );
        
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if( res != CURLE_OK )
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
         
        /* always cleanup */ 
        curl_easy_cleanup(curl);
        fclose( pFile );
    }
    return 0;
}
