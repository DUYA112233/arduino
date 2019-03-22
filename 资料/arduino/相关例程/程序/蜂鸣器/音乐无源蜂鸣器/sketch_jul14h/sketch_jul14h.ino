 #include "pitches.h"

// 乐曲中的音符
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// 音符持续时间: 4 = 四分音符, 8 = 八分音符 等等:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

void setup() {
  // 顺序加载乐曲中的音符
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // 用1S为基准计算音符持续时间
    //比如 四分音符 = 1000 / 4, 八分音符 = 1000/8, 等等
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // 设置一个最小的时间间隔来区分音符
  // 一般正常音符的1.3倍效果较好
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // 停止播放音乐
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
