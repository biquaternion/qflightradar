# qflightradar
flightradar24 data view (REST-based)

Для нормальной работы проекту требуется подпроект QtRestApiRequester (https://github.com/Bragaman/QtRestApiRequester.git).
Его надо положить относительно этого двумя каталогами выше, либо поменять путь в строчке
include(../../QtRestApiRequester.git/requester/requester.pri)
файла FlightRadar.pro
и в исходниках нужно подправить константу 
const QString Requester::httpTemplate
, удалив из неё "api"
