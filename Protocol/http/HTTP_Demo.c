#include <string.h>
#include <stdio.h>
#include <stdint.h>

char text[30];
char temp[10];

/**
  * @brief   组HTTP POST报文
  * @param   pkt   报文缓存指针
  * @param   key   API_KEY定义在Main.c文件中，需要根据自己的设备修改
  *	@param 	 devid 设备ID，定义在main.c文件中，需要根据自己的设备修改
  *	@param 	 dsid  数据流ID
  *	@param 	 val   字符串形式的数据点的值
  * @retval  整个包的长度
  */
uint32_t HTTP_PostPkt(char *pkt, const char *key, int data)
{
  *pkt = 0;
	memset(temp, 0, 10);
	memset(text, 0, 30);
	
	sprintf(temp,"%d", data);

	strcat(text, "auth_key=");
	strcat(text, key);
	strcat(text, "&");
	strcat(text, "data=");
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
