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
void CTandPTtoFirst();

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
unsigned int GetVolLevel();

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

//Сохраняем пл!   AAA
void SavePlaylist(char *fn);

// Возвращется трек по номеру в пл
char * GetCurrentTrack();

// Возвращется играющий трек по номеру в пл
char * GetPlayedTrack();

// Ослабление альфа-канала
char * Lighten(char * source);

// Перерисовка
void PL_Redraw();

#endif
