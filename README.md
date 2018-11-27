# qflightradar
flightradar24 data view (REST-based)

# eng
requires https://github.com/Bragaman/QtRestApiRequester.git.
Also it needs to remove substring "api" from Requester::httpTemplate string definition.

# rus
Для нормальной работы проекту требуется подпроект QtRestApiRequester (https://github.com/Bragaman/QtRestApiRequester.git).
в его исходниках нужно подправить константу 
const QString Requester::httpTemplate
, удалив из неё "api"
