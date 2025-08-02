# BMP Console Application (C++)

A lightweight C++ console application for working with BMP image files (24-bit or 32-bit). It reads a BMP image containing only black and white pixels, displays it using ASCII characters, draws a red cross (X) over the image, displays the updated image again, and saves the modified result to a new BMP file.

---

## 🧠 Features

- ✅ Read 24-bit and 32-bit BMP files using raw binary parsing (no external BMP libraries)
- ✅ Display image in the console using characters:
    - `' '` (space) for white (RGB 255,255,255)
    - `'█'` (block) for black (RGB 0,0,0)
- ✅ Draw an `X` (cross) over the image using Bresenham’s line algorithm
- ✅ Save the modified image to a new BMP file
- ✅ Fully cross-platform (Linux)

---

## 🛠 Requirements

- C++17 or later
- Linux (tested)
- `clang++`

---

## 🔧 Building the Project and Run

```bash
make
```

---

## 🚀 How to Run
```bash
make run
```

##  Sample session:

>> Enter input BMP file name: test.bmp

[Console output of original image]

>> Enter output BMP file name: result.bmp

---

##  📸 BMP File Assumptions

    Only 24-bit and 32-bit BMPs are supported.

    Must use only black (0,0,0) and white (255,255,255) colors.

    Small size recommended (e.g., 50x50 pixels or less).