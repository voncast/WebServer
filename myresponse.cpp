#include "myresponse.h"

myResponse::myResponse(){

}

void myResponse::addStatus(QString sta)
{
        QDateTime date=QDateTime::currentDateTime();
        QString d=date.toString("ddd, dd MMM yyyy hh:mm:ss ");
        d+="GMT";
        res="HTTP/1.1 "+sta+"\r\nDate:"+d+"\r\n";
}
void myResponse::addType(QString type){
    res+="Content-type:"+type+"\r\n";
}
void myResponse::addLength(QString l){
    res+="Accept-Ranges:bytes\r\n";
    res+="Content-length:"+l+"\r\n\r\n";
}
void myResponse::addContent(QString str){
    res+=str;
}
QString myResponse::response(){
    return res;
}
