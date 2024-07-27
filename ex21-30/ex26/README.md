# IP Camera Panoramic July 2024
A study project

## The demon of working with an image. (ENG) 
 The task of one of the demons is to receive and process the image, and at the end give out a ready-made panorama.

### Assembly
 The daemon depends on v4i2rtspserver and libjpeg.

```https://github.com/Dafang-Hacks/Main/tree/master```

 In order not to load the system once again, the daemon takes the same image that the server receives for the web interface. The server itself updates the photo in shared memory once per second. This is a limitation that can be circumvented, but due to backlash, the camera is not able to take photos more often than once every 1.5 seconds. To unload the system, you can greatly reduce the server, but it is important to leave the functionality of v4i2rtspserver-tools. Instructions for building the server are available in the repository.

```http://www.ijg.org/```

 The ljpeg library is used for subsequent work with photos from shared memory. In our case, we used version 9f. You need to compile the library with a compiler from a submodule. In our case, this library was used only by the image daemon and we decided to make a static link. In the modules\ljpeg folder you will find the .sh file that we used to build the library. In our repository you will find a Makefile that will show you how to compile the image daemon when you have the server and ljpeg ready.

### How does it work? Algorithm.
The first stage is initialization. We create, fill the socket and wait for the structure of the motor daemon. 
The second stage is waiting for the start from the tg bot via the .status file. From this stage, the daemon is in an eternal cycle, which can be interrupted either by disabling the motor daemon, or if there are 3 cycles in the status file between cycles. When we receive the start signal, we take the first photo, send a signal to the motor and enter the second eternal cycle, which can only be interrupted by the motor daemon with a completion signal or a socket error.
The third stage of alternate work with the photo and the demon of the motor. The essence of the second eternal cycle is to take a photo, send a signal to the demon of the motor, process the photo and create an artificial delay to stabilize the camera. Upon the correct completion of this stage, the camera returns to its original position, and the bot simultaneously sends a ready-made panorama, which, even in the event of an emergency shutdown of the image daemon, is enlarged and stored in tmp at every third iteration of photo gluing. As a result, we went through the full cycle of creating photos and returned to the second stage.
 
## Демон работы с изображением. (RU)
 Задача одного из демонов получить и обработать изображение, а в конце выдать готовую панораму.

### Сборка
 Демон зависит от v4i2rtspserver и libjpeg. 

```https://github.com/Dafang-Hacks/Main/tree/master```

 Чтобы лишний раз не нагружать систему, демон берет то же изображение, какое получает сервер для веб интерфейса. Сам сервер обновляет фото в разделяемой памяти раз в секунду. Это ограничение, которое можно обойти, но из-за люфта камера не способна делать фото чаще раза в 1.5 секунды. Чтобы разгрузить систему можно сильно урезать сервер, но важно оставить функционал v4i2rtspserver-tools. Инструкции по сборке сервера есть в репозитории.

```http://www.ijg.org/```

  Библиотека ljpeg используется для последующей работы с фото из разделяемой памяти. В нашем случае мы использовали версию 9f. Нужно скомпиллировать библиотеку компилятором из подмодуля. В нашем случае эту библиотеку использовал только демон изображения и мы решили сделать статическую линковку. В папке modules\ljpeg вы найдете .sh файл, которым пользовались мы для сборки библиотеки. В нашем репозитории вы найдете Makefile, который покажет вам как компилировать демона изображения, когда у вас будет готов сервер и ljpeg.

### Как оно работает? Алгоритм.
Первый этап инициализация. Мы создаем, заполняем сокет и ожидаем структуры демона мотора. 
Второй этап ожидание старта от тг бота через файл .status. С этого этапа демон находится в вечном цикле, который можно прервать или отключением демона мотора, или если между циклами в файле статуса будет 3. Когда мы получим сигнал старта делаем первое фото, отправляем сигнал мотору и заходим во второй вечный цикл, который может прервать только демон мотора сигналом о завершении или ошибке сокета.
Третий этап поочередной работы с фото и демоном мотора. Суть второго вечного цикла делать фото, отправлять сигнал демону мотора, обрабатывать фото и создавать искусственную задержку для стабилизации камеры. По корректному завершению этого этапа камера возвращается в исходное положение, а бот параллельно отправляет уже готовую панораму, которая даже в случае аварийного завершения демона изображения наращивается и сохраняется в tmp на каждой третьей итерации склейки фото. В итоге мы прошли полный цикл создания фото и вернулись ко второму этапу.

