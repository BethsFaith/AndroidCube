# Developed with AndroidStudio 

Небольшое приложение для андроид-устройств. 
Используются: 
* JNI для рендера на С++ через GLSurfaceView
* Android Java Activity
* Плагин Android Studio CMake с поддержкой C++

Для запуска потребуется Android Studio.

# Запуск

* [Загрузить Android Studio](https://developer.android.com/studio?hl=ru);
* Запустить Android Studio;
* Открыть каталог с проектом;
* Открыть File/Project Structure;
* Нажать "Download" или "Select" для местоположения NDK;
* Выбрать "Tools"/"Android"/"Sync Project with Gradle Files";
* Нажать "Run".

# Инструкция по применению

Для вращения куба по орбите нажать и удерживать в любом месте экрана (на физическом устройстве) или двигать мышью (на эмуляторе).
Для вращения куба вокруг своей оси по Y провести движение мышью/пальцем вправо или влево.
Режимы вращения переключаются кнопкой, которая находится в левом верхнем углу экрана. 
