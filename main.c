#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

char *ascii = " .:-=+*#%@";

char get_ascii(unsigned char r, unsigned char g, unsigned char b);
char get_ascii(unsigned char r, unsigned char g, unsigned char b) {
  // Converte RGB para intensidade de cinza (fórmula luminância)
  // converte RGB para uma média de brilho
  float brilho = (0.2126f * r + 0.7152f * g + 0.0722f * b);  // percepção visual

  // string com mais tons: do mais escuro ao mais claro
  // const char *tons = "@$B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1}{[]?-_+~i!lI;:,\"^`'. ";
  // const char *tons = "@%#*+=-:. ";
  const char *tons = ".:-=+*#%@";

  int idx = (brilho / 255.0) * (strlen(tons) - 1);
  return tons[idx];
}
void main() {
  int largura, altura, canais;
  unsigned char *img = stbi_load("output/bandeira.png", &largura, &altura, &canais, 3);

  if (!img) {
    printf("Erro ao carregar imagem: %s\n", stbi_failure_reason());
    return ;
  }

  // Para cada pixel, converte em ASCII
  int fator_x = largura / 153;
  int fator_y = altura / 40;

  for (int y = 0; y < altura; y += fator_y) {
    for (int x = 0; x < largura; x += fator_x) {
      int idx = (y * largura + x) * 3;
      unsigned char r = img[idx];
      unsigned char g = img[idx + 1];
      unsigned char b = img[idx + 2];
      printf("%c", get_ascii(r, g, b));
    }
    printf("\n");
  }

  stbi_image_free(img);
  return ;
}