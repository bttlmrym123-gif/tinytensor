# TinyML Tensör ve Quantization (Nicemleme) Demo Projesi - C Dili

Bu proje, C dili kullanılarak yazılmış basit bir TinyML tarzı tensör yapısı ve int8 quantization (nicemleme) uygulamasını göstermektedir.

Amaç, floating point (float) değerlerin gömülü sistemlerde daha az bellek kullanacak şekilde int8 formatına dönüştürülmesini simüle etmektir.

---

## 📌 Projenin Amacı

Gömülü sistemlerde (mikrodenetleyiciler, IoT cihazları vb.) bellek ve işlem gücü oldukça sınırlıdır.

Makine öğrenmesi modellerini bu sistemlerde çalıştırabilmek için:
- Bellek kullanımını azaltmak
- Hesaplama maliyetini düşürmek
- Enerji tüketimini azaltmak

gerekmektedir.

Bu nedenle float (32-bit) değerler, 8-bit tamsayı (int8) formatına dönüştürülür. Bu işleme **Quantization (Nicemleme)** denir.

---

## 🧠 Tensör Nedir?

Tensör, çok boyutlu veri yapısıdır ve makine öğrenmesinin temel yapı taşıdır.

Örnekler:
- Skaler → 0 boyutlu tensör
- Vektör → 1 boyutlu tensör
- Matris → 2 boyutlu tensör
- Daha yüksek boyutlar → N boyutlu tensör

Bu projede 1 boyutlu basitleştirilmiş bir tensör yapısı uygulanmıştır.

---

## 🔢 Quantization (Nicemleme) Formülü

Projede kullanılan temel nicemleme formülü:

Q = (R / S) + Z

Burada:

- R → Gerçek (float) değer  
- S → Ölçek (scale) değeri  
- Z → Sıfır noktası (zero point)  
- Q → Nicemlenmiş int8 değeri  

Elde edilen değer int8 aralığında sınırlandırılır:

- Minimum: -128  
- Maksimum: +127  

Bu sayede taşma (overflow) engellenir.

---

## ⚙️ Kullanılan Teknolojiler

- Programlama Dili: C
- Derleyici: GCC (TDM-GCC 4.9.2 64-bit)
- IDE: Dev-C++
- Platform: Windows

---

## 🧩 Kod Yapısı

Projede şu yapılar bulunmaktadır:

- `enum TensorType` → Veri tipini belirler
- `struct TinyTensor` → Tensör yapısını temsil eder
- `union` → Aynı bellek alanını farklı veri tipleriyle paylaşmayı sağlar
- `quantize()` fonksiyonu → Float → int8 dönüşümünü yapar
- `malloc()` / `free()` → Dinamik bellek yönetimi

---

## 🚀 Derleme ve Çalıştırma

GCC ile derlemek için:

```bash
gcc tinytensor.c -o tensor
.\tensor
