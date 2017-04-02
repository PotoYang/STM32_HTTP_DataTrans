#include <string.h>
#include <stdio.h>
#include <stdint.h>

char text[100];
char temp[10];

/**
  * @brief   组HTTP GET报文
  * @param   pkt   报文缓存指针
  * @param   key   key唯一识别码
  * @param   data  数据
  */
uint32_t HTTP_GetPkt(char *pkt, const char *key, int data)
{
  *pkt = 0;
	memset(temp, 0, 10);
	memset(text, 0, 100);
	
	sprintf(temp,"%d", data);

	strcat(text, "auth_key=");
	strcat(text, key);
	strcat(text, "&");
	strcat(text, "data1=");
	strcat(text, temp);
	strcat(text, "&");
	strcat(text, "data2=");
	strcat(text, temp);
	strcat(text, "&");
	strcat(text, "data3=");
	strcat(text, temp);
	strcat(text, "&");
	strcat(text, "data4=");
	strcat(text, temp);
	strcat(text, "&");
	strcat(text, "data5=");
	strcat(text, temp);
	strcat(text, "&");
	strcat(text, "data6=");
	strcat(text, temp);
	
  strcat(pkt, "GET /Train/getinfo.php?");
  strcat(pkt, text);
	strcat(pkt, " HTTP/1.1\r\n");
  
  strcat(pkt, "Host: 192.168.1.108:8888\r\n");
  
  //strcat(pkt, "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6) Gecko/20050225 Firefox/1.0.1\r\n");
  strcat(pkt, "Connection: Keep-Alive\r\n");
  strcat(pkt, "Cache-Control: no-cache\r\n");
  strcat(pkt, "\r\n\r\n");
  
  return strlen(pkt);
}
