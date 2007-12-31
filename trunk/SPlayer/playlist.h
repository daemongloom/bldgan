#ifndef _PLAYLIST_H_
  #define _PLAYLIST_H_

// Оказалось его перед закрытием еще и останавливать надо... А то такое начинается! :D  AAA
void DisableScroll(void);

// Поднимаем громкость
void VolumeUp();

// Опускаем громкость
void VolumeDown();

// Громкость на ноль
void ToggleVolume();

// Случайный трек
void RandTrack();

//Повторяющийся трек  AAA
void RepeatTrack();

// Для plamode==1  AAA
void NextTrackX();

// Следующий трек пл  AAA
void NextTrack();

// Предыдущий трек пл  AAA
void PreviousTrack();

// Пауза/Воспроизведение
void TogglePlayback();

// Останавливаем проигрывание
void StopAllPlayback();

// Постановка в очередь   AAA
void SetNextPlayed();

// Воспроизведение поставленного в очередь   AAA
void PlaySetTrack();

// Слудующий пл   AAA
void NextPL();

// Предыдущий пл   AAA
void PrevPL();

// Потребовалось для исправления глюка AAA
void CTtoFirst();

// Сделал в две для удобства AAA
void PTtoFirst();

//Пробуем листание вниз AAA
void CTDown();

//Пробуем листание вверх AAA
void CTUp();

// Быстрое листание вниз AAA
void CTDownSpeed(void);

// Быстрое листание вверх AAA
void CTUpSpeed(void);

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
//int GetMP3Tag_v1(const char * fname, MP3Tagv1 * tag);

// Выделим память   AAA
void Memory();

// Для загрузки пл из главного модуля
void LoadingPlaylist(const char * fn);

// Свобода пл!
void FreePlaylist(void);

// Загружаем пл!
int LoadPlaylist(const char * fn);

// Сохраняем пл!   AAA
void SavePlaylist(char *fn);

// Добавляем строку в пл   AAA
void PastLine(char *p);

// Копируем строку в пл   AAA
void CopyLine(char *p);

// Удаляем строку из пл   AAA
void DeleteLine();

// Перемещаем строку в пл вверх   AAA
void MoveLineUp();

// Перемещаем строку в пл вниз   AAA
void MoveLineDown();

// Перемещаем строку в следующий пл   AAA
void MoveLineRight();

// Перемещаем строку в предыдущий пл   AAA
void MoveLineLeft();

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

// Утечка памяти в самом деле достала...   AAA
void MemoryFree();

#endif
