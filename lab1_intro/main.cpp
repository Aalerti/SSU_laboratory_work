#include <iostream>

int             main()         {
    // 1. Ошибка стиля: Google Style требует 2 пробела, а тут хаос.
    int*       leak = new int[10]; // 2. Утечка памяти: выделили через new, но не удалили.

    for(int i=0; i<10; i++){
        leak[i] = i * 2;
        std::cout << "Value: " << leak[i] << std::endl;
    }

    // 3. Ошибка стиля: отсутствие пустой строки в конце файла и лишние пробелы.
    return 0;
}