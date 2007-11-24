#ifndef _PLAYLIST_H_
  #define _PLAYLIST_H_

// Оказалось его перед закрытием еще и останавливать надо... А то такое начинается! :D
void DisableScroll(void);

// Поднимаем громкость
void VolumeUp();

// Опускаем громкость
void VolumeDown();

// Громкость на ноль
void ToggleVolume();

// Случайный трек
void RandTrack();

//Повторяющийся трек
void RepeatTrack();

// Для plamode==1
void NextTrackX();

// Следующий трек пл
void NextTrack();

// Предыдущий трек пл
void PreviousTrack();

// Пауза/Воспроизведение
void TogglePlayback();

// Останавливаем проигрывание
void StopAllPlayback();

// Потребовалось для исправления глюка AAA
void CTtoFirst();

// Сделал в две для удобства AAA
void PTtoFirst();

//Пробуем листание вниз AAA
void CTDown();

//Пробуем листание вверх AAA
void CTUp();

//Листание шопестец вниз AAA
void CTDovnSix();

//Листание шопестец вверх AAA
void CTUpSix();

//Воспроизвести AAA
void PlayTrackUnderC();

//Раскраска AAA
//int * TextColor(int my_x,int my_y,int c,int w,int out_ws,int i);       Не вышла оптимизация, ибо некогда

// Выдаем текущий статус
char GetPlayingStatus();

// Устанавливаем статус
void SetPlayingStatus(char PS);

// Громкость
unsigned short GetVolLevel();

// Установим указатель на проигрываемую мелодию...
void SetPHandle(short ph);

// Возвращает кол-во треков в загруженном пл
int GetTC();

// Возвращаем структуру mp3-тега
int GetMP3Tag_v1(const char * fname, MP3Tagv1 * tag);

// Для загрузки пл из главного модуля
void LoadingPlaylist(const char * fn);

// Свобода пл!
void FreePlaylist(void);

// Загружаем пл!
int LoadPlaylist(const char * fn);

// Сохраняем пл!   AAA
void SavePlaylist(char *fn);

// Удаляем строку из пл   AAA
void DeleteLine();

// Перемещаем строку в пл вверх   AAA
void MoveLineUp();

// Перемещаем строку в пл вниз   AAA
void MoveLineDown();

// Возвращется трек по номеру в пл
char * GetCurrentTrack();

// Возвращется играющий трек по номеру в пл
char * GetPlayedTrack();

// Перерисовка
void PL_Redraw();

// Полоса прокрутки   AAA
void BandRoll();

//Ищем файлы в папке   AAA
void FindMusic(const char *dir, int i);

#endif
