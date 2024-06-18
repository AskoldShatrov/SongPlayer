# Описание проекта

***SongPlayer*** - музыкальный плеер, разработанный с использованием Qt и QML, который позволяет пользователям воспроизводить музыку, управлять плейлистами и выполнять поиск музыкальных треков через REST API.

![alt text](https://github.com/AskoldShatrov/SongPlayer/blob/main/about/image-1.png)


## Особенности
Воспроизведение музыки: Поддержка аудиофайлов различных форматов.

Плейлисты: Управление плейлистами, включая добавление, удаление и переключение треков.

Поиск музыки: Возможность поиска музыки через внешний REST API.

## Технологии
Qt и QML: Основной фреймворк и язык разметки.

Qt Network: Для работы с сетью и выполнения HTTP запросов.

QMediaPlayer: Для воспроизведения аудиофайлов.

SongPlayer использует REST API для поиска музыки. 


## Реализация

Классом отвечающим за поиск песен по запросу пользователя, является AudioSearchModel.

В момент, когда пользователь вводит название песни, вызывается метод searchSong, в котором создается GET запрос к внешнему API jamendo.


Для этой задачи используется класс Qt Network:
```cpp QUrlQuery query;
query.addQueryItem("client_id", k_clientId);
query.addQueryItem("namesearch", name);
query.addQueryItem("format", "json");

m_reply = m_networkManager.get(QNetworkRequest(k_requestUrl + "?" + query.toString()));
connect(m_reply, &QNetworkReply::finished, this, &AudioSearchModel::parseData);
```

![alt text](https://github.com/AskoldShatrov/SongPlayer/blob/main/about/image-2.png)

В методе parseData данные из ответа API разбираются с использованием QJsonDocument и QJsonObject:

```cpp QByteArray data = m_reply->readAll();
QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
QJsonObject headers = jsonDocument["headers"].toObject();
```

После получения headers осуществляется проверка статуса ответа: проверяется, был ли запрос успешным, сравнивая значение поля status в headers объекте с строкой "success".

```cpp

if (headers["status"].toString() == "success") {
   
} else {

    qWarning() << headers["error_string"];
}

```
Если запрос был успешным, извлекаются результаты из jsonDocument. Результаты представлены в виде QJsonArray под ключом "results".

Для каждого результата в массиве результатов происходит следующее:

+ Создается новый объект AudioInfo.

+ Извлекаются данные о треке (название, исполнитель, URL изображения, URL аудиофайла) из каждого объекта результата и устанавливаются в AudioInfo.

+ Объект AudioInfo добавляется в список аудиозаписей m_audioList.


После обработки всех результатов, модель данных обновляется, чтобы отобразить новые данные в интерфейсе пользователя.

```cpp
beginResetModel();
endResetModel();
```

Управление добавлением, переключением песен, поведение слайдера, переключением плейлистов вынесено в класс PlayerController, использующий объекты AudioInfo для доступа к данным каждого трека.

![alt text](https://github.com/AskoldShatrov/SongPlayer/blob/main/about/image-3.png)
