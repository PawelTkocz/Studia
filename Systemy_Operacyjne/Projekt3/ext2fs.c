/*
 * Oświadczam, że zapoznałem(-am) się z regulaminem prowadzenia zajęć
 * i jestem świadomy(-a) konsekwencji niestosowania się do podanych tam zasad.
 */
#ifdef STUDENT
/* Imię i nazwisko, numer indeksu: Paweł Tkocz, 332168 */
#endif

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <unistd.h>

#include "ext2fs_defs.h"
#include "ext2fs.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
#undef DEBUG
#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

/* Call this function when an unfixable error has happened. */
static noreturn void panic(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
  exit(EXIT_FAILURE);
}

/* Number of lists containing buffered blocks. */
#define NBUCKETS 16

/* Since majority of files in a filesystem are small, `idx` values will be
 * usually low. Since ext2fs tends to allocate blocks at the beginning of each
 * block group, `ino` values are less predictable. */
#define BUCKET(ino, idx) (((ino) + (idx)) % NBUCKETS)

/* That should give us around 64kB worth of buffers. */
#define NBLOCKS (NBUCKETS * 4)

/* Structure that is used to manage buffer of single block. */
typedef struct blk {
  TAILQ_ENTRY(blk) b_hash;
  TAILQ_ENTRY(blk) b_link;
  uint32_t b_blkaddr; /* block address on the block device */
  uint32_t b_inode;   /* i-node number of file this buffer refers to */
  uint32_t b_index;   /* block index from the beginning of file */
  uint32_t b_refcnt;  /* if zero then block can be reused */
  void *b_data;       /* raw data from this buffer */
} blk_t;

typedef TAILQ_HEAD(blk_list, blk) blk_list_t;

/* BLK_ZERO is a special value that reflect the fact that block 0 may be used to
 * represent a block filled with zeros. You must not dereference the value! */
#define BLK_ZERO ((blk_t *)-1L)

/* All memory for buffers and buffer management is allocated statically.
 * Using malloc for these would introduce unnecessary complexity. */
static alignas(BLKSIZE) char blkdata[NBLOCKS][BLKSIZE];
static blk_t blocks[NBLOCKS];
static blk_list_t buckets[NBUCKETS]; /* all blocks with valid data */
static blk_list_t lrulst;            /* free blocks with valid data */
static blk_list_t freelst;           /* free blocks that are empty */

/* File descriptor that refers to ext2 filesystem image. */
static int fd_ext2 = -1;

/* How many i-nodes fit into one block? */
#define BLK_INODES (BLKSIZE / sizeof(ext2_inode_t))

/* How many block pointers fit into one block? */
#define BLK_POINTERS (BLKSIZE / sizeof(uint32_t))

/* Properties extracted from a superblock and block group descriptors. */
static size_t inodes_per_group;      /* number of i-nodes in block group */
static size_t blocks_per_group;      /* number of blocks in block group */
static size_t group_desc_count;      /* numbre of block group descriptors */
static size_t block_count;           /* number of blocks in the filesystem */
static size_t inode_count;           /* number of i-nodes in the filesystem */
static size_t first_data_block;      /* first block managed by block bitmap */
static ext2_groupdesc_t *group_desc; /* block group descriptors in memory */

/*
 * Buffering routines.
 */

/* Opens filesystem image file and initializes block buffers. */
static int blk_init(const char *fspath) {
  if ((fd_ext2 = open(fspath, O_RDONLY)) < 0)
    return errno;

  /* Initialize list structures. */
  TAILQ_INIT(&lrulst);
  TAILQ_INIT(&freelst);
  for (int i = 0; i < NBUCKETS; i++)
    TAILQ_INIT(&buckets[i]);

  /* Initialize all blocks and put them on free list. */
  for (int i = 0; i < NBLOCKS; i++) {
    blocks[i].b_data = blkdata[i];
    TAILQ_INSERT_TAIL(&freelst, &blocks[i], b_link);
  }

  return 0;
}

/* Allocates new block buffer. */
static blk_t *blk_alloc(void) {
  blk_t *blk = NULL;

  /* Initially every empty block is on free list. */
  if (!TAILQ_EMPTY(&freelst)) {
#ifdef STUDENT
    /* TODO */
    /*Pobieram ostatni blok z listy wolnych bloków
      i usuwam go z tej listy*/
    blk = TAILQ_LAST(&freelst, blk_list);
    TAILQ_REMOVE(&freelst, blk, b_link);
#endif /* !STUDENT */
    return blk;
  }

  /* Eventually free list will become exhausted.
   * Then we'll take the last recently used entry from LRU list. */
  if (!TAILQ_EMPTY(&lrulst)) {
#ifdef STUDENT
    /* TODO */
    /*każdy blok znajdujący się na liście lrulst wciąż znajduje się na jednej
      z list bloków zaalokowanych. Zatem kiedy potrzebujemy zaalokować
      jeden z takich bloków, należy go usunąć zarówno z listy lrulst jak i
      z odpowiedniej listy bloków zaalokowanych (bucket)*/
    blk = TAILQ_LAST(&lrulst, blk_list);
    blk_list_t *bucket = &buckets[BUCKET(blk->b_inode, blk->b_index)];
    TAILQ_REMOVE(&lrulst, blk, b_link);
    TAILQ_REMOVE(bucket, blk, b_hash);
#endif /* !STUDENT */
    return blk;
  }

  /* No buffers!? Have you forgot to release some? */
  panic("Free buffers pool exhausted!");
}

/* Acquires a block buffer for file identified by `ino` i-node and block index
 * `idx`. When `ino` is zero the buffer refers to filesystem metadata (i.e.
 * superblock, block group descriptors, block & i-node bitmap, etc.) and `off`
 * offset is given from the start of block device. */
static blk_t *blk_get(uint32_t ino, uint32_t idx) {
  blk_list_t *bucket = &buckets[BUCKET(ino, idx)];
  blk_t *blk = NULL;

  /* Locate a block in the buffer and return it if found. */
#ifdef STUDENT
  /* TODO */
  blk_t *i;
  TAILQ_FOREACH (i, bucket, b_hash) {
    if (i->b_inode == ino && i->b_index == idx) {
      /*jeśli refcnt bloku jest równe 0, tzn że blok został
        wstawiony na listę lrulst. Należy go więc z tej listy
        usunąć, jako że znów przechowuje dane, które nie mogą
        zostać zmodyfikowane*/
      if (i->b_refcnt == 0)
        TAILQ_REMOVE(&lrulst, i, b_link);
      i->b_refcnt++;
      return i;
    }
  }
#endif /* !STUDENT */

  long blkaddr = ext2_blkaddr_read(ino, idx);
  debug("ext2_blkaddr_read(%d, %d) -> %ld\n", ino, idx, blkaddr);
  if (blkaddr == -1)
    return NULL;
  if (blkaddr == 0)
    return BLK_ZERO;
  if (ino > 0 && !ext2_block_used(blkaddr))
    panic("Attempt to read block %d that is not in use!", blkaddr);

  blk = blk_alloc();
  blk->b_inode = ino;
  blk->b_index = idx;
  blk->b_blkaddr = blkaddr;
  blk->b_refcnt = 1;

  ssize_t nread =
    pread(fd_ext2, blk->b_data, BLKSIZE, blk->b_blkaddr * BLKSIZE);
  if (nread != BLKSIZE)
    panic("Attempt to read past the end of filesystem!");

  TAILQ_INSERT_HEAD(bucket, blk, b_hash);
  return blk;
}

/* Releases a block buffer. If reference counter hits 0 the buffer can be
 * reused to cache another block. The buffer is put at the beginning of LRU list
 * of unused blocks. */
static void blk_put(blk_t *blk) {
  if (--blk->b_refcnt > 0)
    return;

  TAILQ_INSERT_HEAD(&lrulst, blk, b_link);
}

/*
 * Ext2 filesystem routines.
 */

/* Reads block bitmap entry for `blkaddr`. Returns 0 if the block is free,
 * 1 if it's in use, and EINVAL if `blkaddr` is out of range. */
int ext2_block_used(uint32_t blkaddr) {
  if (blkaddr >= block_count)
    return EINVAL;
  int used = 0;
#ifdef STUDENT
  /* TODO */
  /*pobieram odpowiedni blok tablicy deskryptorów grup bloków*/
  int block_group = (blkaddr - first_data_block) / blocks_per_group;
  int offset_from_start =
    (EXT2_GDOFF + block_group * sizeof(ext2_groupdesc_t)) / BLKSIZE;
  blk_t *desc_table_blk = blk_get(0, offset_from_start);

  /*z pobranego bloku odczytuję deskryptor grupy bloków, do której należy blok o
    adresie blkaddr*/
  int desc_entr_per_blk = BLKSIZE / sizeof(ext2_groupdesc_t);
  int blk_entry_offset = block_group % desc_entr_per_blk;
  ext2_groupdesc_t *group_desc =
    (ext2_groupdesc_t *)desc_table_blk->b_data + blk_entry_offset;

  /*pobieram blok przechowujący bitmapę bloków*/
  uint32_t block_bitmap_addr = group_desc->gd_b_bitmap;
  blk_t *block_bitmap = blk_get(0, block_bitmap_addr);

  /*odczytuję wartość bitu bitmapy, który odpowiada blokowi o adresie blkaddr*/
  int blk_group_idx = (blkaddr - 1) % blocks_per_group;
  uint8_t *ptr = block_bitmap->b_data + blk_group_idx / 8;
  used = (*ptr >> (blk_group_idx % 8)) & 1;

  /*odkładam pobrane bloki*/
  blk_put(desc_table_blk);
  blk_put(block_bitmap);
#endif /* !STUDENT */
  return used;
}

/* Reads i-node bitmap entry for `ino`. Returns 0 if the i-node is free,
 * 1 if it's in use, and EINVAL if `ino` value is out of range. */
int ext2_inode_used(uint32_t ino) {
  if (!ino || ino >= inode_count)
    return EINVAL;
  int used = 0;
#ifdef STUDENT
  /* TODO */
  /*pobieram odpowiedni blok tablicy deskryptorów grup bloków*/
  int block_group = (ino - 1) / inodes_per_group;
  int offset_from_start =
    (EXT2_GDOFF + block_group * sizeof(ext2_groupdesc_t)) / BLKSIZE;
  blk_t *desc_table_blk = blk_get(0, offset_from_start);

  /*z pobranego bloku odczytuję deskryptor grupy bloków, do której należy
   i-węzeł o numerze ino*/
  int desc_entr_per_blk = BLKSIZE / sizeof(ext2_groupdesc_t);
  int blk_entry_offset = block_group % desc_entr_per_blk;
  ext2_groupdesc_t *group_desc =
    (ext2_groupdesc_t *)desc_table_blk->b_data + blk_entry_offset;

  /*pobieram blok przechowujący bitmapę i-węzłów*/
  uint32_t inode_bitmap_addr = group_desc->gd_i_bitmap;
  blk_t *inode_bitmap = blk_get(0, inode_bitmap_addr);

  /*odczytuję wartość bitu bitmapy, który odpowiada i-węzłowi o numerze ino*/
  int inode_group_ind = (ino - 1) % inodes_per_group;
  uint8_t *ptr = inode_bitmap->b_data + inode_group_ind / 8;
  used = (*ptr >> (inode_group_ind % 8)) & 1;

  /*odkładam pobrane bloki*/
  blk_put(desc_table_blk);
  blk_put(inode_bitmap);
#endif /* !STUDENT */
  return used;
}

/* Reads i-node identified by number `ino`.
 * Returns 0 on success. If i-node is not allocated returns ENOENT. */
static int ext2_inode_read(off_t ino, ext2_inode_t *inode) {
#ifdef STUDENT
  /* TODO */
  /*zwracam ENOENT jeśli i-węzeł o numerze ino nie jest zaalokowany*/
  if (!ext2_inode_used(ino))
    return ENOENT;

  /*pobieram odpowiedni blok tablicy deskryptorów grup bloków*/
  int block_group = (ino - 1) / inodes_per_group;
  int offset_from_start =
    (EXT2_GDOFF + block_group * sizeof(ext2_groupdesc_t)) / BLKSIZE;
  blk_t *desc_table_blk = blk_get(0, offset_from_start);

  /*z pobranego bloku odczytuję deskryptor grupy bloków, do której należy
   i-węzeł o numerze ino*/
  int desc_entr_per_blk = BLKSIZE / sizeof(ext2_groupdesc_t);
  int blk_entry_offset = block_group % desc_entr_per_blk;
  ext2_groupdesc_t *group_desc =
    (ext2_groupdesc_t *)desc_table_blk->b_data + blk_entry_offset;

  /*pobieram odpowiedni blok tablicy i-węzłów*/
  uint32_t inode_table_addr = group_desc->gd_i_tables;
  int inode_group_ind = (ino - 1) % inodes_per_group;
  blk_t *inode_table_blk =
    blk_get(0, inode_table_addr + inode_group_ind / BLK_INODES);

  /*z pobranego bloku odczytuję i-węzeł o numerze ino i przekopiowuję jego
  zawartość*/
  int inode_blk_offset = inode_group_ind % BLK_INODES;
  ext2_inode_t *inode_ptr =
    (ext2_inode_t *)inode_table_blk->b_data + inode_blk_offset;
  memcpy(inode, inode_ptr, sizeof(ext2_inode_t));

  /*odkładam pobrane bloki*/
  blk_put(desc_table_blk);
  blk_put(inode_table_blk);
#endif /* !STUDENT */
  return 0;
}

/* Returns block pointer `blkidx` from block of `blkaddr` address. */
static uint32_t ext2_blkptr_read(uint32_t blkaddr, uint32_t blkidx) {
#ifdef STUDENT
  /* TODO */
  blk_t *blk = blk_get(0, blkaddr);
  uint32_t *res = (uint32_t *)blk->b_data + blkidx;
  blk_put(blk);
  return *res;
#endif /* !STUDENT */
  return 0;
}

/* Translates i-node number `ino` and block index `idx` to block address.
 * Returns -1 on failure, otherwise block address. */
long ext2_blkaddr_read(uint32_t ino, uint32_t blkidx) {
  /* No translation for filesystem metadata blocks. */
  if (ino == 0)
    return blkidx;

  ext2_inode_t inode;
  if (ext2_inode_read(ino, &inode))
    return -1;

    /* Read direct pointers or pointers from indirect blocks. */
#ifdef STUDENT
  /* TODO */
  /*w i-węźle znajduje się 12 bezpośrednich wskaźników na bloki
    Poza tym jeden wskaźnik na blok pośredni, jeden na podwójnie
    pośredni i jeden na potrójnie pośredni. Bloki te gwarantują
    dostęp do następującej liczby bloków:
    blok pośredni = BLK_POINTERS bloków
    blok podwójnie pośredni = BLK_POINTERS^2 bloków
    blok potrójnie pośredni = BLK_POINTERS^3 bloków*/
  static const uint32_t direct_blocks = 12;
  /*liczba dostępnych bloków z wykorzystaniem tylko bezpośrednich wskaźników*/
  static const uint32_t max1 = direct_blocks;
  /*liczba dostępnych bloków z wykorzystaniem bezpośrednich wskaźników i bloku
   * pośredniego*/
  static const uint32_t max2 = max1 + BLK_POINTERS;
  /*liczba dostępnych bloków z wykorzystaniem bezpośrednich wskaźników, bloku
   * pośredniego i podwójnie pośredniego*/
  static const uint32_t max3 = max2 + BLK_POINTERS * BLK_POINTERS;
  /*liczba wszystkich dostępnych dla i-węzła bloków, a więc również z
   * wykorzystaniem bloku potrójnie pośredniego*/
  static const uint32_t max4 =
    max3 + BLK_POINTERS * BLK_POINTERS * BLK_POINTERS;

  uint32_t *i_blocks = inode.i_blocks;

  if (blkidx < max1) {
    /*blok, do którego wskaźnik jest zapisany bezpośrednio w i-węźle*/
    return *(i_blocks + blkidx);
  } else if (blkidx < max2) {
    /*blok, do którego wskaźnik jest zapisany w bloku pośrednim*/
    return ext2_blkptr_read(*(i_blocks + direct_blocks),
                            blkidx - direct_blocks);
  } else if (blkidx < max3) {
    /*blok, do którego wskaźnik jest zapisany w bloku podwójnie pośrednim*/
    blk_t *dbl_blk = blk_get(0, *(i_blocks + direct_blocks + 1));
    int indirect_block_number = (blkidx - max2) / BLK_POINTERS;
    int indirect_block_offset = (blkidx - max2) % BLK_POINTERS;
    uint32_t *dbl_blocks = dbl_blk->b_data;
    blk_put(dbl_blk);
    return ext2_blkptr_read(*(dbl_blocks + indirect_block_number),
                            indirect_block_offset);
  } else if (blkidx < max4) {
    /*blok, do którego wskaźnik jest zapisany w bloku potrójnie pośrednim*/
    /*pobieram blok potrójnie pośredni*/
    blk_t *trpl_blk = blk_get(0, *(i_blocks + direct_blocks + 2));
    int dbl_block_number = (blkidx - max3) / (BLK_POINTERS * BLK_POINTERS);
    int dbl_block_offset = (blkidx - max3) % (BLK_POINTERS * BLK_POINTERS);
    uint32_t *trpl_blocks = trpl_blk->b_data;

    /*z pobranego bloku odczytuję wskaźnik na odpowiedni blok podwójnie pośredni
      i pobieram go*/
    blk_t *dbl_blk = blk_get(0, *(trpl_blocks + dbl_block_number));
    int indirect_block_number = dbl_block_offset / BLK_POINTERS;
    int indirect_block_offset = dbl_block_offset % BLK_POINTERS;
    uint32_t *dbl_blocks = dbl_blk->b_data;

    blk_put(trpl_blk);
    blk_put(dbl_blk);
    return ext2_blkptr_read(*(dbl_blocks + indirect_block_number),
                            indirect_block_offset);
  }
#endif /* !STUDENT */
  return -1;
}

/* Reads exactly `len` bytes starting from `pos` position from any file (i.e.
 * regular, directory, etc.) identified by `ino` i-node. Returns 0 on success,
 * EINVAL if `pos` and `len` would have pointed past the last block of file.
 *
 * WARNING: This function assumes that `ino` i-node pointer is valid! */
int ext2_read(uint32_t ino, void *data, size_t pos, size_t len) {
#ifdef STUDENT
  /* TODO */
  if (len == 0)
    return 0;

  /*jeśli ino != 0 to sprawdzam, czy nie nastąpi próba odczytania bajtów
    znajdujących się za ostatnim blokiem pliku - w takim przypadku zwracam
    EINVAL*/
  if (ino != 0) {
    ext2_inode_t inode;
    ext2_inode_read(ino, &inode);
    int blocks_number = (inode.i_size % BLKSIZE) ? inode.i_size / BLKSIZE + 1
                                                 : inode.i_size / BLKSIZE;
    if ((pos + len - 1) / BLKSIZE >= (uint32_t)blocks_number) {
      return EINVAL;
    }
  }

  /*pobieram pierwszy blok, od którego rozpoczyna się czytanie*/
  int blk_index = pos / BLKSIZE;
  blk_t *blk = blk_get(ino, blk_index);

  /*zmienna hole przechowuje informację, czy pobrany blok jest dziurą w pliku
    a więc czy przechowuje same 0*/
  bool hole = (blk == BLK_ZERO);
  int blk_offset = pos % BLKSIZE;
  int bytes_avail = BLKSIZE - blk_offset;

  /*jeśli wszystkie bajty, które chcemy odczytać znajdują się na pobranym bloku,
    kopiuję ich wartość i zwracam 0*/
  if (len <= (size_t)bytes_avail) {
    if (hole)
      memset(data, 0, len);
    else {
      memcpy(data, blk->b_data + blk_offset, len);
      blk_put(blk);
    }
    return 0;
  }

  /*jeśli nie, to kopiuję wszystkie dostępne bajty z bloku*/
  if (hole)
    memset(data, 0, bytes_avail);
  else {
    memcpy(data, blk->b_data + blk_offset, bytes_avail);
    blk_put(blk);
  }

  int bytes_left = len - bytes_avail;
  int bytes_copied = bytes_avail;

  /*dopóki nie przekopiuję wszystkich bajtów powtarzam w pętli następujące
    operacje: pobieram następny blok pliku, przekopiowuję odpowiednią liczbę
    jego bajtów i odkładam pobrany blok*/
  while (bytes_left) {
    blk = blk_get(ino, ++blk_index);
    int bytes_to_copy = min(bytes_left, (int)BLKSIZE);
    if (blk == BLK_ZERO)
      memset(data + bytes_copied, 0, bytes_to_copy);
    else {
      memcpy(data + bytes_copied, blk->b_data, bytes_to_copy);
      blk_put(blk);
    }
    bytes_left -= bytes_to_copy;
    bytes_copied += bytes_to_copy;
  }

  return 0;
#endif /* !STUDENT */
  return EINVAL;
}

/* Reads a directory entry at position stored in `off_p` from `ino` i-node that
 * is assumed to be a directory file. The entry is stored in `de` and
 * `de->de_name` must be NUL-terminated. Assumes that entry offset is 0 or was
 * set by previous call to `ext2_readdir`. Returns 1 on success, 0 if there are
 * no more entries to read. */
#define de_name_offset offsetof(ext2_dirent_t, de_name)

int ext2_readdir(uint32_t ino, uint32_t *off_p, ext2_dirent_t *de) {
#ifdef STUDENT
  /* TODO */
  ext2_inode_t inode;
  ext2_inode_read(ino, &inode);
  int blocks_number = (inode.i_size % BLKSIZE) ? inode.i_size / BLKSIZE + 1
                                               : inode.i_size / BLKSIZE;

  /*Jeśli w katalogu nie ma więcej wpisów, zwracam 0*/
  int blk_index = *off_p / BLKSIZE;
  if (blk_index >= blocks_number)
    return 0;

  /*pobieram odpowiedni blok katalogu i odczytuję odpowiedni wpis*/
  blk_t *blk = blk_get(ino, blk_index);
  int blk_offset = *off_p % BLKSIZE;
  ext2_dirent_t *dirent = blk->b_data + blk_offset;
  *off_p += dirent->de_reclen;

  /*jeśli wartość ino pobranego wpisu katalogu wynosi 0, to wpis ten
    traktujemy jako usunięty, należy go pominąć - wywołuję ext2_readdir
    rekurencyjnie, na zmodyfikowanej wartości off_p*/
  if (dirent->de_ino == 0) {
    blk_put(blk);
    return ext2_readdir(ino, off_p, de);
  }

  /*jeśli wartość ino pobranego wpisu katalogu jest różna od 0, to
    przekopiowuję wartość tego wpisu i zwracam 1*/
  memcpy(de, dirent, sizeof(ext2_dirent_t));
  memcpy((void *)de + de_name_offset + dirent->de_namelen, "", 1);
  blk_put(blk);
  return 1;
#endif /* !STUDENT */
  return 0;
}

/* Read the target of a symbolic link identified by `ino` i-node into buffer
 * `buf` of size `buflen`. Returns 0 on success, EINVAL if the file is not a
 * symlink or read failed. */
int ext2_readlink(uint32_t ino, char *buf, size_t buflen) {
  int error;

  ext2_inode_t inode;
  if ((error = ext2_inode_read(ino, &inode)))
    return error;

    /* Check if it's a symlink and read it. */
#ifdef STUDENT
  /* TODO */
  /*jeśli plik nie jest dowiązaniem symbolicznym, zwracam EINVAL*/
  if (!(inode.i_mode & EXT2_IFLNK))
    return EINVAL;

  if (buflen > inode.i_size)
    buflen = inode.i_size;

  /*dowiązanie symboliczne jest zapisane w postaci stringa, będącego ścieżką do
   * pliku*/
  /*Jeśli długość tego string jest mniejsza niż 60, jest on zapisany w miejscu
    i-węzła przeznaczonym na wskaźniki na bloki. Wpp jest on zapisany na
    pierwszym bloku*/
  if (inode.i_size < 60) {
    memcpy(buf, &inode.i_blocks, buflen);
    return 0;
  } else {
    if (!ext2_read(ino, buf, 0, buflen))
      return 0;
    else
      return EINVAL;
  }
#endif /* !STUDENT */
  return ENOTSUP;
}

/* Read metadata from file identified by `ino` i-node and convert it to
 * `struct stat`. Returns 0 on success, or error if i-node could not be read. */
int ext2_stat(uint32_t ino, struct stat *st) {
  int error;

  ext2_inode_t inode;
  if ((error = ext2_inode_read(ino, &inode)))
    return error;

    /* Convert the metadata! */
#ifdef STUDENT
  /* TODO */
  st->st_ino = ino;
  st->st_mode = inode.i_mode;
  st->st_nlink = inode.i_nlink;
  st->st_uid = inode.i_uid;
  st->st_gid = inode.i_gid;
  st->st_size = (((long)inode.i_size_high) << 32) | inode.i_size;
  st->st_atime = inode.i_atime;
  st->st_mtime = inode.i_mtime;
  st->st_ctime = inode.i_ctime;
#endif /* !STUDENT */
  return ENOTSUP;
}

/* Reads file identified by `ino` i-node as directory and performs a lookup of
 * `name` entry. If an entry is found, its i-inode number is stored in `ino_p`
 * and its type in stored in `type_p`. On success returns 0, or EINVAL if `name`
 * is NULL or zero length, or ENOTDIR is `ino` file is not a directory, or
 * ENOENT if no entry was found. */
int ext2_lookup(uint32_t ino, const char *name, uint32_t *ino_p,
                uint8_t *type_p) {
  int error;

  if (name == NULL || !strlen(name))
    return EINVAL;

  ext2_inode_t inode;
  if ((error = ext2_inode_read(ino, &inode)))
    return error;

#ifdef STUDENT
  /* TODO */
  /*Jeśli plik nie jest katalogiem, zwracam ENOTDIR*/
  if (!(inode.i_mode & EXT2_IFDIR))
    return ENOTDIR;

  uint32_t dir_offset = 0;
  ext2_dirent_t dirent;
  /*W pętli odczytuję wartość kolejnych wpisów w katalogu i porównuję
    nazwy plików, do których się odnoszą, ze stringiem name. Jeśli odnajdę
    odpowiedni wpis, ustawiam wartość ino_p i type_p na odpowiednie wartości*/
  while (ext2_readdir(ino, &dir_offset, &dirent)) {
    if (strcmp(dirent.de_name, name) == 0) {
      *ino_p = dirent.de_ino;
      *type_p = dirent.de_type;
      return 0;
    }
  }
#endif /* !STUDENT */

  return ENOENT;
}

/* Initializes ext2 filesystem stored in `fspath` file.
 * Returns 0 on success, otherwise an error. */
int ext2_mount(const char *fspath) {
  int error;

  if ((error = blk_init(fspath)))
    return error;

  /* Read superblock and verify we support filesystem's features. */
  ext2_superblock_t sb;
  ext2_read(0, &sb, EXT2_SBOFF, sizeof(ext2_superblock_t));

  debug(">>> super block\n"
        "# of inodes      : %d\n"
        "# of blocks      : %d\n"
        "block size       : %ld\n"
        "blocks per group : %d\n"
        "inodes per group : %d\n"
        "inode size       : %d\n",
        sb.sb_icount, sb.sb_bcount, 1024UL << sb.sb_log_bsize, sb.sb_bpg,
        sb.sb_ipg, sb.sb_inode_size);

  if (sb.sb_magic != EXT2_MAGIC)
    panic("'%s' cannot be identified as ext2 filesystem!", fspath);

  if (sb.sb_rev != EXT2_REV1)
    panic("Only ext2 revision 1 is supported!");

  size_t blksize = 1024UL << sb.sb_log_bsize;
  if (blksize != BLKSIZE)
    panic("ext2 filesystem with block size %ld not supported!", blksize);

  if (sb.sb_inode_size != sizeof(ext2_inode_t))
    panic("The only i-node size supported is %d!", sizeof(ext2_inode_t));

    /* Load interesting data from superblock into global variables.
     * Read group descriptor table into memory. */
#ifdef STUDENT
  /* TODO */
  inodes_per_group = sb.sb_ipg;
  blocks_per_group = sb.sb_bpg;
  block_count = sb.sb_bcount;
  inode_count = sb.sb_icount;
  group_desc_count = block_count / blocks_per_group;
  first_data_block = sb.sb_first_dblock;
  group_desc = (ext2_groupdesc_t *)EXT2_GDOFF;
  return 0;
#endif /* !STUDENT */
  return ENOTSUP;
}
