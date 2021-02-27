### Driver MacOS

Для программирования планы `NodeMCU` надо установить драйвер [cp2102](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

### Arduino lib
- [OneWire](https://www.arduino.cc/reference/en/libraries/onewire/)
- [DallasTemperature](https://www.arduino.cc/reference/en/libraries/dallastemperature/)

### Hardware
Распиновка.
- do, d1 - питание сенсоров
- a0 - аналооговый вход для датчиков давления
- d4 - цифровой вход для датчиков температуры
- gnd - общий минус

### Connect

Открыть браузер по адресу `http://192.168.4.1`


### Вопросы
1. Только 1 аналогоовый вхоод. Надо добавлять мультиплесор
2. Подвисает веб-сервер. Попрообовать gz.страницы или connection-close.