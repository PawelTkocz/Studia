/*
Paweł Tkocz 332168
Oświadczam, że jestem jedynym autorem kodu źródłowego
W moim rozwiązaniu skorzystałem z gotowych funkcji pomocniczych
znajdujących się w pliku mm-implicit.c do których należą:
bt_size(), bt_used(), bt_free(), bt_footer(), bt_fromptr(), morecore(),
bt_get_prevfree(), bt_clr_prevfree(), bt_set_prevfree() i bt_payload()
Dodatkowo korzystam z funkcji round_up(), która była zdefiniowana.

Opis działania programu:

Zawartość zajętego bloku:
Na każdy zajęty blok składa się nagłówek (4 bajty) i payload o rozmiarze
określony w trakcie wywołania malloc. W nagłówku zakodowane są rozmiar bloku i
dwie dodatkowe informacje. Ponieważ rozmiar bloku jest zawsze wielokrotnością
16 bajtów, ostatnie 4 bity są zawsze równe 0. Z tego powodu można je wykorzystać
do zakodowania dodatkowych informacji na temat bloku. Ostatni bit koduje
informację o tym, czy blok jest zajęty (1) czy wolny (0). Przedostatni bit
koduje informację o tym, czy blok bezpośrednio go poprzedzający jest zajęty (1)
czy wolny (0).

Zawartość wolnego bloku:
Na każdy wolny blok składa się nagłówek i stopka (obie po 4 bajty - nagłówek
pierwsze 4, a stopka ostatnie 4 bajty bloku)(stopka przechowuje dokładnie te
same informacje co nagłówek) Dodatkowo, pierwsze 4 bajty po nagłówku zawierają
zakodowany wskaźnik na następny wolny blok na liście wolnych bloków, kolejne 4
bajty zawierają zakodowany wskaźnik na poprzedni wolny blok na liście. Ponieważ
wiemy, że rozmiar sterty jest ograniczony i nie przekracza 4GiB = 2^32 bajtów,
możemy skompresować wskaźniki do 4 bajtów: na 4 bajtach, czyli 32 bitach można
zapisać offset bloku względem początku sterty. Aby obliczyć rzeczywisty wskaźnik
bloku wystarczy do tak zakodowanego offsetu dodać adres początku sterty, który z
kolei można odczytać wykorzystując funkcję mem_heap_lo().

Moja implementacja korzysta z techniki zarządzania wolnymi blokami segregated
fits. Na stercie przechowuję wskaźniki na 9 list wolnych bloków, każda z nich
przechowuje bloki o rozmiarach z różnych przedziałów: [lista 1: 16 bajtów]
[lista 2: 32-48 bajtów] [lista 3: 64-128 bajtów] [lista 4: 144-256 bajtów]
[lista 5: 272-512 bajtów] [lista 6: 528-1024 bajtów] [lista 7: 1040-2048 bajtów]
[lista 8: 2064-4096 bajtów] [lista 9: 4112 bajtów i większe]. Wskaźniki na każdą
z tych list przechowuję na samym początku sterty. Skompresowałem je w sposób
opisany wyżej do 4 bajtów, zatem na ich przechowanie przeznaczyłem pierwsze 36
bajtów na stercie. Bezpośrednio po nich, na stercie umieściłem 8-bajtowy,
zaalokowany blok startowy (składa się jedynie z nagłówka i stopki) oraz
4-bajtowy, zaalokowany blok końcowy (składa się tylko z nagłówka). Bloki te
ułatwiają operacje alokowania bloków i ich zwalniania na skrajnych przypadkach
(blok, na którym wykonywana jest operacja to pierwszy lub ostatni blok na
stercie).

Każda z 9 list wolnych bloków została zaimplementowana jako dwukierunkowa lista
zapętlająca się. Zapętlająca, bo umożliwia to dokładanie bloków na koniec listy
w czasie stałym. Przeprowadzając testy zauważyłem, że program uzyskiwał
najlepsze wyniki stosując metodę dodawania wolnych bloków FIFO, stąd
zdecydowałem się na taką implementację list.
Ponieważ listy są zapętlające, do ich przeszukiwania korzystam z pętli "do
while" gdzie przeszukiwanie kończy się, kiedy dojdziemy do bloku, z którego
zaczynaliśmy

Opis najważniejszych funkcji:

Przydział bloku (malloc):
Funkcja malloc korzysta z dwóch funkcji: find_fit() oraz place()
find_fit() przeszukuje odpowiednie listy wolnych bloków i zwraca adres bloku,
pod którym można zaalokować zażądaną ilość pamięci
place() usuwa blok o adresie zwróconym przez find_fit() z listy wolnych bloków
i tworzy nagłówek zaalokowanego bloku - blok jest teraz gotowy do użytku

find_fit() dokładniej:
funkcja find_fit(size) oblicza, która lista zwiera bloki o rozmiarach z
przedziału, do którego należy size. Następnie wykorzystując metodę first_fit()
przeszukuje tę listę w poszukiwaniu wystarczająco dużego bloku. Jeśli taki blok
znajdzie, zwróci jego adres (jeśli blok był większy niż wymagano, podzieli go na
dwa mniejsze i przydzieli je do odpowiednich list). Jeśli na liście nie będzie
znajdował się wystarczająco duży blok, find_fit zacznie szukać wystarczająco
dużego bloku na kolejnych listach (zawierających bloki o coraz większych
rozmiarach). Jeśli na żadnej z list nie znajdzie się odpowiednio duży blok,
find_fit wywoła funkcję extend_heap(), która zwiększy rozmiar sterty o wymaganą
wartość - doda wystarczająco duży nowy, wolny blok do jednej z list. Następnie
find_fit woła się rekurencyjnie - tym razem mamy pewność, że znajdzie
odpowiednio duży blok

Zwalnianie bloku (free):
funkcja free oznacza blok jako wolny przez ustawienie odpowiedniego nagłówka i
stopki funkcją bt_make, a następnie wywołuje funkcję coalesce(), która złącza
sąsiadujące wolne bloki

coalesce() dokładniej:
Funkcja łączy sąsiadujące wolne bloki. Rozważamy cztery przypadki, w zależności
od tego, czy blok poprzedzający i następujący po właśnie zwolnionym są wolne czy
zajęte. W każdym z przypadków, jeśli następuje połączenie wolnych bloków, należy
przed tym połączeniem usunąć z listy wolnych bloków odpowiednie bloki (te które
teraz staną się częścią większego). Funkcja tworzy nagłówki i stopki nowych
wolnych bloków, ustawia bit PREVFREE dla bloków, u których ta wartość uległa
zmianie. Na koniec dodaje utworzony wolny blok do odpowiedniej listy wolnych
bloków i zwraca jego adres

funckja realloc():
Do funkcji realloc dodałem małe optymalizacje, które pozwalają uniknąć
przenoszenia całego bloku w niektórych przypadkach. Jeśli funkcja realloc chce
zmniejszyć zaalokowany blok o mniej niż 16 bajtów, nie trzeba przenosić bloku.
Jeśli funkcja realloc() chce zmniejszyć zaalokowany blok o więcej niż 16 bajtów,
to można podzielić zaalokowany blok na dwa mniejsze. Ten drugi można oznaczyć
jako wolny i dodać do listy wolnych bloków. Jeśli funkcja realloc() chce
zwiększyć rozmiar zaalokowanego bloku o x bajtów, a bezpośrednio po tym bloku
znajduje się wolny blok o rozmiarze większym lub równym x, to również można
uniknąć kopiowania całego bloku. Jeżeli następny blok jest większy niż x o co
najmniej 16 bajtów, można go podzielić na dwa wolne bloki - pierwszy z nich
oddać do zaalokowania, a drugi dodać do listy wolnych bloków. Jeśli nie
nastąpiła żadna z tych sytuacji należy wywołać malloc() i przekopiować zawartość
starego bloku do nowego. Na koniec można w takiej sytuacji zwolnić blok.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
//#define DEBUG
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

typedef int32_t word_t; /*sterta jest podzielona na 4 bajtowe słowa*/
typedef enum {
  FREE = 0,     /* Blok jest wolny */
  USED = 1,     /* Blok jest używany */
  PREVFREE = 2, /* Poprzedni blok jest wolny */
} bt_flags;

static word_t *free_lists; /*wskaźnik na pierwszą z list wolnych bloków*/
static void *heap_start;   /*adres, pod jakim znajduje się początek sterty*/
static word_t
  *first_block; /*adres, pod jakim znajduje się pierwszy blok na stercie*/
static size_t word_size; /*rozmiar słowa na które podzielone jest sterta*/
static int free_lists_number; /*liczba list wolnych bloków zastosowana w modelu
                                 segregated fits*/

/*funkcja zaokrągla size w górę do najbliższej wielokrotności ALIGNMENT*/
static size_t round_up(size_t size) {
  return (size + ALIGNMENT - 1) & -ALIGNMENT;
}

/*funkcja odczytuje z nagłówka/stopki bloku jego rozmiar*/
static inline word_t bt_size(word_t *bt) {
  return *bt & ~(USED | PREVFREE);
}

/*funkcja odczytuje z nagłówka/stopki bloku informację, czy jest zajęty*/
static inline int bt_used(word_t *bt) {
  return *bt & USED;
}

/*funkcja odczytuje z nagłówka/stopki bloku informację, czy jest wolny*/
static inline int bt_free(word_t *bt) {
  return !(*bt & USED);
}

/*funkcja otrzymuje wskaźnik na nagłówek bloku i zwraca wskaźnik na jego
 * stopkę*/
static inline word_t *bt_footer(word_t *bt) {
  return (void *)bt + bt_size(bt) - word_size;
}

/*funkcja otrzymuje wskaźnik na payload bloku i zwraca wskaźnik na jego
 * nagłówek*/
static inline word_t *bt_fromptr(void *ptr) {
  return (word_t *)ptr - 1;
}

/*funkcja tworzy nagłówek i\lub stopkę dla bloku o podanych parametrach*/
static inline void bt_make(word_t *bt, size_t size, bt_flags flags) {
  word_t bt_val = size | flags;
  *bt = bt_val;
  if (!(flags & USED)) {
    word_t *footer = bt_footer(bt);
    *footer = bt_val;
  }
}

/*funkcja zwraca informację czy poprzedzający blok jest wolny*/
static inline bt_flags bt_get_prevfree(word_t *bt) {
  return *bt & PREVFREE;
}

/*funkcja zeruje bit PREVFREE w nagłówku bloku bt*/
static inline void bt_clr_prevfree(word_t *bt) {
  if (bt)
    *bt &= ~PREVFREE;
}

/*funkcja ustawia bit PREVFREE w nagłówku bloku bt*/
static inline void bt_set_prevfree(word_t *bt) {
  *bt |= PREVFREE;
}

/*funkcja otrzymuje wskaźnik na nagłówek bloku i zwraca wskaźnik na jego
 * payload*/
static inline void *bt_payload(word_t *bt) {
  return bt + 1;
}

/*funkcja zwraca adres następnego na stercie bloku*/
static inline word_t *bt_next(word_t *bt) {
  return (void *)bt + bt_size(bt);
}

/*funkcja zwraca informację, czy blok bezpośrednio po bt jest wolny*/
static inline bt_flags bt_get_nextfree(word_t *bt) {
  return bt_free(bt_next(bt));
}

/*funkcja otrzymuje offset względem początku sterty i oblicza pełen adres*/
static inline word_t *get_full_address(int offset) {
  return (word_t *)(heap_start + offset);
}

/*funkcja otrzymuje pełen adres i zwraca offset względem początku sterty*/
static inline word_t get_short_address(word_t *bt) {
  unsigned int mask = -1;
  return (int)((long)bt & mask);
}

/*funkcja zwraca wskaźnik na następny po bt wolny blok na liście*/
static inline word_t *next_free_block(word_t *bt) {
  return get_full_address(*(bt + 1));
}

/*funkcja zwraca wskaźnik na wolny blok, który znajduje się przed bt na liście*/
static inline word_t *prev_free_block(word_t *bt) {
  return get_full_address(*(bt + 2));
}

/*funkcja ustawia wskaźnik na następny wolny blok dla bloku bp*/
static inline void set_next_free_block(word_t *bp, word_t *next) {
  word_t *next_block = bp + 1;
  *next_block = get_short_address(next);
}

/*funkcja ustawia wskaźnik na poprzedni wolny blok dla bloku bp*/
static inline void set_prev_free_block(word_t *bp, word_t *prev) {
  word_t *prev_block = bp + 2;
  *prev_block = get_short_address(prev);
}

/*funkcja zwraca wskaźnik na nagłówek bloku bezpośrednio przed blokiem bt
funkcja ta jest wywoływana tylko jeśli blok poprzedzający bt jest wolny
zatem ma stopkę, z której można odczytać informację o jego rozmiarze*/
static inline word_t *bt_prev(word_t *bt) {
  return (void *)bt - bt_size(bt - 1);
}

/*funkcja oblicza rozmiar bloku do zaalokowania z uwzględnieniem 4 bajtów na
 * nagłówek*/
static inline size_t blksz(size_t payload) {
  return round_up(payload + word_size);
}

/*funkcja odpowiedzialna za zwiększanie rozmiaru sterty*/
static void *morecore(size_t size) {
  void *ptr = mem_sbrk(size);
  if (ptr == (void *)-1)
    return NULL;
  return ptr;
}

/*funkcja zwraca offset listy przechowującej bloki o rozmiarach
z przedziału odpowiadającemu size względem pierwszej listy wolnych bloków*/
static inline int free_list_offset(size_t size) {
  if (size <= 16)
    return 0;
  if (size <= 48)
    return 1;
  if (size <= 128)
    return 2;
  if (size <= 256)
    return 3;
  if (size <= 512)
    return 4;
  if (size <= 1024)
    return 5;
  if (size <= 2048)
    return 6;
  if (size <= 4096)
    return 7;
  return 8;
}

/*funkcja zwraca wskaźnik na listę wolnych bloków
  o rozmiarach z przedziału odpowiadającemu argumentowi size*/
static word_t *free_list_address(size_t size) {
  return free_lists + free_list_offset(size);
}

/*funkcja zwraca wskaźnik na następną w kolejności wolną listę,
  tzn zawierającą wolne bloki z następnego przedziału rozmiarów*/
static inline word_t *next_free_list_address(word_t *free_list) {
  word_t *next = free_list + 1;
  if (next >= free_lists + free_lists_number)
    return NULL;
  return next;
}

/*funkcja zwraca wskaźnik na pierwszy blok na liście zakodowanej
na stercie pod adresem free_list_address*/
static inline word_t *free_list_first_block(word_t *free_list_address) {
  int offset = *free_list_address;
  if (offset == 0)
    return NULL;
  return get_full_address(offset);
}

/*funkcja ustawia wskaźnik pierwszego bloku na liście na new_free_list,
gdzie NULL jest kodowany jako 0*/
static inline void set_free_list(word_t *free_list_address,
                                 word_t *new_free_list) {
  if (new_free_list == NULL)
    *free_list_address = 0;
  else
    *free_list_address = get_short_address(new_free_list);
}

/*funkcja wstawia blok bp na koniec listy, której pierwszym blokiem jest
 * free_list_first_block*/
static void fifo(word_t *bp, word_t *free_list_first_block) {
  word_t *prev_block = prev_free_block(free_list_first_block);
  set_next_free_block(bp, free_list_first_block);
  set_prev_free_block(bp, prev_block);
  set_next_free_block(prev_block, bp);
  set_prev_free_block(free_list_first_block, bp);
}

/*funkcja znajduje listę wolnych bloków o rozmiarach odpowiadających rozmiarowi
bloku bp i dodaje go do tej listy*/
static void add_free_block(word_t *bp) {
  word_t *free_list_addr = free_list_address(bt_size(bp));
  word_t *first_block = free_list_first_block(free_list_addr);
  if (first_block == NULL) {
    /*lista jest obecnie pusta*/
    set_free_list(free_list_addr, bp);
    set_prev_free_block(bp, bp);
    set_next_free_block(bp, bp);
    return;
  }
  fifo(bp, first_block);
}

/*funkcja znajduje listę wolnych bloków, na której znajduje się blok bp i usuwa
 * go z tej listy*/
static void del_free_block(word_t *bp) {
  word_t *free_list_addr = free_list_address(bt_size(bp));
  word_t *first_block = free_list_first_block(free_list_addr);
  word_t *prev = prev_free_block(bp);
  word_t *next = next_free_block(bp);
  if (prev == bp) {
    /*na liście znajduje się tylko jeden blok*/
    set_free_list(free_list_addr, NULL);
    return;
  }
  set_next_free_block(prev, next);
  set_prev_free_block(next, prev);
  if (first_block == bp)
    set_free_list(free_list_addr, next);
}

/*funkcja złącza sąsiadujące ze sobą wolne bloki i tak utworzony wolny blok
dodaje do odpowiedniej listy wolnych bloków*/
static void *coalesce(void *bp) {
  bool prev_free = bt_get_prevfree(bp);
  bool next_free = bt_get_nextfree(bp);
  size_t size = bt_size(bp);
  word_t *next_block = bt_next(bp);
  word_t *prev_block;
  if (!prev_free && !next_free) {
    /*Opcja 1: Zajęty__bp__Zajęty*/
    bt_set_prevfree(next_block);
  } else if (!prev_free && next_free) {
    /*Opcja 2: Zajęty__bp__Wolny*/
    size += bt_size(next_block);
    bt_make(bp, size, FREE);
    del_free_block(next_block);
  } else if (prev_free && !next_free) {
    /*Opcja 3: Wolny__bp__Zajęty*/
    prev_block = bt_prev(bp);
    del_free_block(prev_block);
    size += bt_size(prev_block);
    bt_make(prev_block, size, FREE | bt_get_prevfree(prev_block));
    bt_set_prevfree(next_block);
    bp = prev_block;
  } else {
    /*Opcja 4: Wolny__bp__Wolny*/
    prev_block = bt_prev(bp);
    del_free_block(prev_block);
    del_free_block(next_block);
    size += bt_size(prev_block) + bt_size(next_block);
    bt_make(prev_block, size, FREE | bt_get_prevfree(prev_block));
    bp = prev_block;
  }
  add_free_block(bp);
  return bp;
}

/*funkcja dodaje wolny blok o rozmiarze size na koniec sterty*/
static void *extend_heap(size_t size) {
  size = round_up(size);
  word_t *block_payload = morecore(size);
  if (block_payload == NULL)
    return NULL;
  word_t *bt = bt_fromptr(block_payload);
  bt_make(bt, size, FREE | bt_get_prevfree(bt));
  bt_make(bt_next(bt), 0, USED | PREVFREE);
  return coalesce(bt);
}

/*funkcja przygotowuje stertę i zmienne globalne*/
int mm_init(void) {
  word_size = sizeof(word_t);
  free_lists_number = 9;
  if (morecore(free_lists_number * sizeof(word_t) + 3 * word_size) == NULL)
    return -1;

  heap_start = mem_heap_lo();
  free_lists = heap_start;

  /*wskaźniki na wolne listy ustawiamy początkowo na NULL*/
  for (int i = 0; i < free_lists_number; i++)
    set_free_list(free_lists + i, NULL);

  /*tworzę blok startowy i blok końcowy*/
  word_t *start_block = heap_start + free_lists_number * sizeof(word_t);
  bt_make(start_block, 2 * word_size, USED);
  word_t *end_block = start_block + 2;
  bt_make(end_block, 0, USED);
  first_block = end_block;

  return 0;
}

/*funkcja znajduje pierwszy na liście blok, który jest wystarczająco duży,
by zmieścić size bajtów i zwraca jego adres. Jeśli znaleziony blok jest
większy niż size, funkcja dzieli go na dwa mniejsze, drugi z utworzony w
ten sposób bloków dodaje do odpowiedniej listy*/
static void *first_fit(size_t size, word_t *free_list_addr) {
  word_t *first_block = free_list_first_block(free_list_addr);
  if (first_block == NULL)
    return NULL;
  word_t *bp = first_block;
  do {
    size_t block_size = bt_size(bp);
    if (size == block_size)
      return bp;
    if (size < block_size) {
      /*podziel blok na dwa mniejsze, drugą część dodaj do odpowiedniej listy*/
      del_free_block(bp);
      bt_make(bp, size, FREE);
      add_free_block(bp);
      word_t *next_block = bt_next(bp);
      bt_make(next_block, block_size - size, FREE | PREVFREE);
      add_free_block(next_block);
      return bp;
    }
    bp = next_free_block(bp);
  } while (bp != first_block);
  return NULL;
}

/*funkcja przeszukuje wszystkie listy wolnych bloków, które mogą zawierać
wystarczająco duży blok, by pomieścić size bajtów. Jeśli żadna z list nie
zawiera wystarczająco dużego bloku, funkcja dodaje na koniec sterty
wystarczająco duży wolny blok i wołając siebie rekurencyjnie, zwraca go jako
odpowiedni blok*/
static word_t *find_fit(size_t size) {
  word_t *free_list_addr = free_list_address(size);
  word_t *fit;
  for (word_t *list_addr = free_list_addr; list_addr != NULL;
       list_addr = next_free_list_address(list_addr)) {
    fit = first_fit(size, list_addr);
    if (fit != NULL)
      return fit;
  }
  /*na żadnej z list nie znajduje się wystarczająco duży blok*/
  if (extend_heap(size) == NULL)
    return NULL;
  /*mamy pewność, że po wywołaniu extend_heap(size) rekurencyjne wywołanie
  find_fit() tym razem znajdzie odpowiednio duży blok*/
  return find_fit(size);
}

/*funkcja umieszcza na stercie blok bp*/
static void place(word_t *bp) {
  size_t block_size = bt_size(bp);
  del_free_block(bp);
  bt_make(bp, block_size, USED);
  bt_clr_prevfree(bt_next(bp));
}

/*funkcja alokuje blok na size bajtów*/
void *malloc(size_t size) {
  if (size == 0)
    return NULL;
  size = blksz(size);
  word_t *block = find_fit(size);
  if (block != NULL) {
    place(block);
    return bt_payload(block);
  }
  return NULL;
}

/*funkcja zwalnia blok spod adresu ptr*/
void free(void *ptr) {
  if (ptr == NULL || mem_heap_lo() > ptr || mem_heap_hi() < ptr)
    return;

  word_t *bt = bt_fromptr(ptr);
  size_t size = bt_size(bt);
  bt_make(bt, size, FREE | bt_get_prevfree(bt));
  coalesce(bt);
}

void *realloc(void *old_ptr, size_t size) {
  if (size == 0) {
    free(old_ptr);
    return NULL;
  }
  if (!old_ptr)
    return malloc(size);

  word_t *bp = bt_fromptr(old_ptr);
  size_t old_size = bt_size(bp);
  size_t block_size = blksz(size);
  if (block_size == old_size)
    return old_ptr;
  else if (block_size < old_size) {
    /*podziel zaalokowany blok na dwa mniejsze, drugą część dodaj do
    odpowiedniej listy wolnych bloków*/
    bt_make(bp, block_size, bt_get_prevfree(bp) | USED);
    word_t *next = bt_next(bp);
    bt_make(next, old_size - block_size, FREE);
    coalesce(next);
    return old_ptr;
  } else {
    size_t extend_size = block_size - old_size;
    word_t *next = bt_next(bp);
    size_t next_size = bt_size(next);
    if (bt_free(next) && next_size >= extend_size) {
      /*jeśli następny na stercie blok jest wolny i wystarczająco duży
      można go zaalokować i uniknąć w ten sposób kopiowania zawartości bloku*/
      if (next_size == extend_size) {
        del_free_block(next);
        bt_make(bp, old_size + next_size, bt_get_prevfree(bp) | USED);
        bt_clr_prevfree(bt_next(bp));
        return old_ptr;
      } else {
        /*blok jest większy niż potrzeba, można podzielić go na dwa mniejsze*/
        del_free_block(next);
        bt_make(bp, block_size, bt_get_prevfree(bp) | USED);
        next = bt_next(bp);
        bt_make(next, next_size - extend_size, FREE);
        add_free_block(next);
        return old_ptr;
      }
    }
  }
  /*realloc chce zwiększyć rozmiar zaalokowanego bloku, a następny blok albo nie
  jest wolny albo nie jest wystarczająco duży. Trzeba zaalokować zupełnie nowy
  blok i przekopiować do niego zawartość starego*/
  word_t *new_ptr = malloc(size);
  if (!new_ptr)
    return NULL;
  memcpy(new_ptr, old_ptr, old_size);
  free(old_ptr);
  return new_ptr;
}

void *calloc(size_t nmemb, size_t size) {
  size_t bytes = nmemb * size;
  void *new_ptr = malloc(bytes);

  if (new_ptr)
    memset(new_ptr, 0, bytes);

  return new_ptr;
}

/*Od tego miejsca wszystkie funkcje to funkcje pomocnicze służące do testowania
 * programu*/

static word_t *wanted_block;

/*funkcja wywołuje funkcję test_function() na każdym bloku z listy
i zwraca fałsz jeśli test_function zwróciło fałsz dla pewnego bloku*/
static bool foreach_block_on_free_list(word_t *free_list_addr,
                                       bool test_function(word_t *)) {
  word_t *first_block = free_list_first_block(free_list_addr);
  if (first_block == NULL)
    return true;
  word_t *bp = first_block;
  do {
    if (test_function(bp) == false)
      return false;
    bp = next_free_block(bp);
  } while (bp != first_block);
  return true;
}

/*funkcja wywołuje funkcję test_function() na każdym bloku z każdej listy
wolnych bloków i zwraca fałsz, jeśli test_function zwróciło fałsz dla pewnego
bloku*/
static bool foreach_free_block(bool test_function(word_t *)) {
  word_t *free_list = free_lists;
  while (free_list != NULL) {
    if (foreach_block_on_free_list(free_list, test_function) == false)
      return false;
    free_list = next_free_list_address(free_list);
  }
  return true;
}

/*funkcja wywołuje funkcję test_function() na każdym bloku ze sterty*/
static bool foreach_block_on_heap(bool test_function(word_t *)) {
  word_t *bp = first_block;
  while (bt_size(bp) != 0) {
    if (test_function(bp) == false)
      return false;
    bp = bt_next(bp);
  }
  return true;
}

/*funkcja zwraca prawdę jeśli blok bp jest wolny*/
static bool block_marked_as_free(word_t *bp) {
  return bt_free(bp);
}

/*funkcja zwraca fałsz jeśli blok bp i blok bezpośrednio po bp są wolne*/
static bool no_two_free_blocks_in_row(word_t *bp) {
  if (bt_free(bp) && bt_get_nextfree(bp))
    return false;
  return true;
}

/*funkcja zwraca prawdę, jeśli wskaźniki na następny wolny i poprzedni wolny
blok na liście wskazują na adresy na stercie*/
static bool free_block_pointers_ok_range(word_t *bp) {
  word_t *next = next_free_block(bp);
  word_t *prev = prev_free_block(bp);
  word_t *last_block = mem_heap_hi() + 1 - word_size;
  return (next >= first_block && prev >= first_block && next <= last_block &&
          prev <= last_block);
}

/*funkcja zwraca prawdę, jeśli bp i wanted_block to dwa różne bloki*/
static bool blocks_not_equal(word_t *bp) {
  return bp != wanted_block;
}

/*funkcja zwraca prawdę, jeśli na którejś z list wolnych bloków znajduje się
 * blok bp*/
static bool on_free_lists(word_t *bp) {
  wanted_block = bp;
  return !foreach_free_block(blocks_not_equal);
}

/*funkcja zwraca fałsz, jeśli blok jest wolny ale nie znajduje się na żadnej z
 * list wolnych bloków*/
static bool if_free_then_on_free_lists(word_t *bp) {
  return (bt_used(bp) || on_free_lists(bp));
}

/*funkcja zwraca prawdę, jeśli wskaźniki na następny i poprzedni wolny blok
wskazują na nagłówki wolnych bloków*/
static bool free_block_pointers_begin(word_t *bp) {
  word_t *next = next_free_block(bp);
  word_t *prev = prev_free_block(bp);
  return (on_free_lists(next) && on_free_lists(prev));
}

/*funkcja zwraca prawdę jeśli bit PREVFREE bloku po bp zawiera informację zgodną
 * z rzeczywistością*/
static bool prev_free_ok(word_t *bp) {
  word_t *next = bt_next(bp);
  return (bt_get_prevfree(next) && bt_free(bp)) ||
         (!bt_get_prevfree(next) && bt_used(bp));
}

/*funkcja wypisuje wszystkie bloki na stercie*/
static void print_heap() {
  /*
  int i = 1;
  word_t *bp = first_block;
  if (bp == NULL)
    return;
  while (bt_size(bp) != 0) {
    printf("----------\n");
    printf("Blok nr %d\n", i++);
    printf("Rozmiar: %d\n", bt_size(bp));
    if (bt_used(bp))
      printf("Stan: zajęty\n");
    else
      printf("Stan: wolny\n");
    printf("Wskaźnik na nagłówek: %p\n", bp);
    printf("Poprzedni blok wolny: %d\n", bt_get_prevfree(bp));
    bp = bt_next(bp);
  }
  printf("----------\n");
  */
}

/*funkcja wypisuje bloki z listy wolnych bloków*/
static void print_free_list(word_t *free_list_addr) {
  /*
  word_t *first_block = free_list_first_block(free_list_addr);
  if (first_block == NULL) {
    printf("     -     \n");
    return;
  }
  word_t *bp = first_block;
  int i = 1;
  do {
    printf("............\n");
    printf("Blok numer %d\n", i++);
    printf("Rozmiar bloku: %d\n", bt_size(bp));
    printf("Wskaźnik na nagłówek: %p\n", bp);
    printf("Wskaźnik na następny wolny blok: %p\n", next_free_block(bp));
    printf("Wskaźnik na poprzedni wolny blok: %p\n", prev_free_block(bp));
    bp = next_free_block(bp);
  } while (bp != first_block);
  printf("............\n");
  */
}

/*funkcja wypisuje wszystkie listy wolnych bloków*/
static void print_free_lists() {

  // int i = 1;
  word_t *free_list = free_lists;
  while (free_list != NULL) {
    // printf("*************\n");
    // printf("Lista wolnych bloków numer %d\n", i++);
    print_free_list(free_list);
    free_list = next_free_list_address(free_list);
  }
}

/*funkcja kończąca program w wypadku naruszenia niezmienników opisanych w
 * mm_checkheap()*/
static void exit_program() {
  print_heap();
  print_free_lists();
  exit(EXIT_FAILURE);
}

/*funkcja sprawdzająca poprawność działania programu*/
void mm_checkheap(int verbose) {
  if (foreach_free_block(&block_marked_as_free) == false) {
    printf("Blok znajdujący się na liście wolnych bloków nie jest oznaczony "
           "jako wolny\n");
    exit_program();
  }
  if (foreach_block_on_heap(&no_two_free_blocks_in_row) == false) {
    printf("Na stercie znajdują się dwa przyległe, wolne bloki\n");
    exit_program();
  }
  if (foreach_free_block(&free_block_pointers_ok_range) == false) {
    printf("Wskaźniki wolnego bloku na następny lub poprzedni wolny blok na "
           "liście wskazują poza stertę");
    exit_program();
  }
  if (foreach_free_block(&free_block_pointers_begin) == false) {
    printf("Wskaźniki wolnego bloku na następny lub poprzedni wolny blok na "
           "liście nie wskazują na początek wolnego bloku\n");
    exit_program();
  }
  if (foreach_block_on_heap(&if_free_then_on_free_lists) == false) {
    printf("Blok oznaczony jako wolny nie znajduje się na żadnej z list "
           "wolnych bloków\n");
    exit_program();
  }
  if (foreach_block_on_heap(&prev_free_ok) == false) {
    printf("Flaga PREVFREE bloku nie zgadza się z rzeczywistym stanem\n");
    exit_program();
  }
}
