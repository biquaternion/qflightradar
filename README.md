# qflightradar
flightradar24 data view (REST-based)

# eng
requires https://github.com/Bragaman/QtRestApiRequester.git (put it in ../.., or change line 11 in .pro to your path).
Also it needs to remove substring "api" from Requester::httpTemplate string definition.

# rus
Для нормальной работы проекту требуется подпроект QtRestApiRequester (https://github.com/Bragaman/QtRestApiRequester.git).
Его надо положить относительно этого двумя каталогами выше, либо поменять путь в строчке
include(../../QtRestApiRequester.git/requester/requester.pri)
файла FlightRadar.pro
и в исходниках нужно подправить константу 
const QString Requester::httpTemplate
, удалив из неё "api"
