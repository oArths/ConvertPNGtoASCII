#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_BUFFER 100000
void alterar_cor_vscode();

int main() {
  alterar_cor_vscode();
  return 0;
}

// Função para alterar a cor do terminal no VSCode
void alterar_cor_vscode() {
  char *home = getenv("USERPROFILE");
  if (home == NULL) {
    printf("Não foi possível localizar o diretório do usuário.\n");
  }

  char settingsPath[MAX_BUFFER];
  snprintf(settingsPath, sizeof(settingsPath), "%s\\AppData\\Roaming\\Code\\User\\settings.json", home);

  FILE *file = fopen(settingsPath, "r");
  if (!file) {
    printf("Não foi possível abrir %s para leitura.\n", settingsPath);
  }

  char conteudo[MAX_BUFFER];
  size_t bytesRead = fread(conteudo, 1, MAX_BUFFER - 1, file);
  conteudo[bytesRead] = '\0';
  fclose(file);

  printf("validação iniciada.\n");
  printf("Conteúdo do arquivo: %s\n", conteudo);
  if (strstr(conteudo, "\"terminal.foreground\":\"#6ace46\"") != NULL) {
    printf("A configuração de cor já está definida.\n");
    return;
  }

  const char *custom_terminal_colors =
      ",\n  \"workbench.colorCustomizations\": {\n"
      "    \"terminal.background\":\"#131212\",\n"
      "    \"terminal.foreground\":\"#6ace46\",\n"
      "    \"terminal.ansiBlack\":\"#1D2021\",\n"
      "    \"terminal.ansiBrightBlack\":\"#665C54\",\n"
      "    \"terminal.ansiBrightBlue\":\"#0D6678\",\n"
      "    \"terminal.ansiBrightCyan\":\"#8BA59B\",\n"
      "    \"terminal.ansiBrightGreen\":\"#237e02\",\n"
      "    \"terminal.ansiBrightMagenta\":\"#8F4673\",\n"
      "    \"terminal.ansiBrightRed\":\"#FB543F\",\n"
      "    \"terminal.ansiBrightWhite\":\"#FDF4C1\",\n"
      "    \"terminal.ansiBrightYellow\":\"#FAC03B\",\n"
      "    \"terminal.ansiBlue\":\"#00a1f9\",\n"
      "    \"terminal.ansiCyan\":\"#8BA59B\",\n"
      "    \"terminal.ansiGreen\":\"#95C085\",\n"
      "    \"terminal.ansiMagenta\":\"#8F4673\",\n"
      "    \"terminal.ansiRed\":\"#FB543F\",\n"
      "    \"terminal.ansiWhite\":\"#A89984\",\n"
      "    \"terminal.ansiYellow\":\"#FAC03B\"\n"
      "  }";

  // Remove o último '}' para evitar JSON inválido
  char *ultimaChave = strrchr(conteudo, '}');
  if (ultimaChave) *ultimaChave = '\0';

  // Junta tudo de volta com as novas configurações
  strcat(conteudo, custom_terminal_colors);
  strcat(conteudo, "\n}");

  file = fopen(settingsPath, "w");
  if (!file) {
    printf("Não foi possível abrir %s para escrita.\n", settingsPath);
  }

  fwrite(conteudo, 1, strlen(conteudo), file);
  fclose(file);

  printf("Configuração de cores adicionada com sucesso ao VSCode!\n");
}
