#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QString>
#include <string>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <sstream>

std::string cifraCesar(const std::string& texto, int chave) {               //Meus códigos em Python, agora em C++
    std::string resultado;                                          // Como o próprio código já mostra, a cifra de césar substitui a letra pelo numero da chave
    for (char letra : texto) {                                      // Por exemplo, se eu colocar a palavra casa e criptografar com a chave 3
        if (isalpha(letra)) {                                       // O resultado esperado é fdvd
            char base = isupper(letra) ? 'A' : 'a';
            char nova_letra = ((letra - base + chave) % 26 + 26) % 26 + base;
            resultado += nova_letra;
        } else {
            resultado += letra;
        }
    }
    return resultado;
}

std::string decifraCesar(const std::string& texto, int chave) {         // Função de decifrar, pega o texto criptografado, e subtrai pelo valor da chave
    return cifraCesar(texto, -chave);
}

std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";                // cifra monoalfabetica necessita que o alfabeto esteja declarado, para que cada letra seja
                                                                    // substituida por outra.
std::string cifraMonoalfabetica(const std::string& texto, const std::string& chave) {
    std::string resultado;
    for (char letra : texto) {
        char upper = toupper(letra);
        auto pos = alfabeto.find(upper);
        if (pos != std::string::npos) {
            resultado += chave[pos];
        } else {
            resultado += letra;
        }
    }
    return resultado;
}

std::string decifraMonoalfabetica(const std::string& texto, const std::string& chave) {
    std::string resultado;
    for (char letra : texto) {
        char upper = toupper(letra);
        auto pos = chave.find(upper);
        if (pos != std::string::npos) {
            resultado += alfabeto[pos];             // Para decifrar só é necessário trocar o valor da chave por alfabeto, assim retorna ao nosso alfabeto =D
        } else {
            resultado += letra;
        }
    }
    return resultado;
}

std::vector<std::vector<char>> gerarMatrizPlayfair(const std::string& chave) {
    std::string alfabeto = "ABCDEFGHIKLMNOPQRSTUVWXYZ";                     // J é tratado como I
    std::string limpaChave;
    std::vector<std::vector<char>> matriz(5, std::vector<char>(5));
    std::string usada;

    for (char c : chave) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (isalpha(c) && usada.find(c) == std::string::npos)
            usada += c;
    }

    for (char c : alfabeto) {
        if (usada.find(c) == std::string::npos)
            usada += c;
    }

    for (int i = 0; i < 25; ++i)
        matriz[i / 5][i % 5] = usada[i];

    return matriz;
}

std::pair<int, int> encontrarPosicao(const std::vector<std::vector<char>>& matriz, char letra) {
    if (letra == 'J') letra = 'I';
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (matriz[i][j] == letra)
                return {i, j};
    return {-1, -1};
}

std::string prepararTextoPlayfair(const std::string& texto) {
    std::string limpo;
    for (char c : texto) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            limpo += c;
        }
    }

    std::string preparado;
    for (size_t i = 0; i < limpo.size(); ++i) {
        char a = limpo[i];
        char b = (i + 1 < limpo.size()) ? limpo[i + 1] : 'X';

        if (a == b) {
            preparado += a;
            preparado += 'X';
        } else {
            preparado += a;
            preparado += b;
            ++i;
        }
    }

    if (preparado.size() % 2 != 0)
        preparado += 'X';

    return preparado;
}

std::string cifraPlayfair(const std::string& texto, const std::string& chave, bool decifrar = false) {
    std::vector<std::vector<char>> matriz = gerarMatrizPlayfair(chave);
    std::string preparado = prepararTextoPlayfair(texto);
    std::string resultado;

    for (size_t i = 0; i < preparado.size(); i += 2) {
        char a = preparado[i];
        char b = preparado[i + 1];

        auto [linha1, col1] = encontrarPosicao(matriz, a);
        auto [linha2, col2] = encontrarPosicao(matriz, b);

        if (linha1 == linha2) {
            resultado += matriz[linha1][(col1 + (decifrar ? 4 : 1)) % 5];
            resultado += matriz[linha2][(col2 + (decifrar ? 4 : 1)) % 5];
        } else if (col1 == col2) {
            resultado += matriz[(linha1 + (decifrar ? 4 : 1)) % 5][col1];
            resultado += matriz[(linha2 + (decifrar ? 4 : 1)) % 5][col2];
        } else {
            resultado += matriz[linha1][col2];
            resultado += matriz[linha2][col1];
        }
    }

    return resultado;
}

int mod26(int n) {
    return (n % 26 + 26) % 26;
}

// Converte letra para número: A=0, B=1, ..., Z=25
int letraParaNumero(char c) {
    return toupper(c) - 'A';
}

// Converte número para letra: 0=A, ..., 25=Z
char numeroParaLetra(int n) {
    return 'A' + mod26(n);
}

std::string cifraHill2x2(const std::string& texto, int a, int b, int c, int d) {
    std::string resultado = "";
    std::string preparado = "";

    // Remove caracteres não alfabéticos e converte para maiúsculo
    for (char ch : texto) {
        if (isalpha(ch)) {
            preparado += toupper(ch);
        }
    }

    // Se número de letras for ímpar, adiciona X
    if (preparado.length() % 2 != 0)
        preparado += 'X';

    for (size_t i = 0; i < preparado.length(); i += 2) {
        int x = letraParaNumero(preparado[i]);
        int y = letraParaNumero(preparado[i + 1]);

        int novoX = mod26(a * x + b * y);
        int novoY = mod26(c * x + d * y);

        resultado += numeroParaLetra(novoX);
        resultado += numeroParaLetra(novoY);
    }

    return resultado;
}
int modInverse(int a, int m) {
    // Calcula o inverso modular de a mod m (ex: a⁻¹ mod 26)
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // Não tem inverso
}

std::string decifraHill2x2(const std::string& texto, int a, int b, int c, int d) {
    std::string resultado = "";

    // Calcular determinante
    int det = mod26(a * d - b * c);
    int detInv = modInverse(det, 26);
    if (detInv == -1) return "Matriz sem inverso mod 26.";

    // Calcular matriz inversa mod 26
    int aInv = mod26(detInv * d);
    int bInv = mod26(-detInv * b);
    int cInv = mod26(-detInv * c);
    int dInv = mod26(detInv * a);

    // Preparar texto (somente letras A-Z)
    std::string preparado = "";
    for (char ch : texto) {
        if (isalpha(ch))
            preparado += toupper(ch);
    }

    // Se for ímpar, completa com X (pode ser resquício da cifra original)
    if (preparado.length() % 2 != 0)
        preparado += 'X';

    for (size_t i = 0; i < preparado.length(); i += 2) {
        int x = letraParaNumero(preparado[i]);
        int y = letraParaNumero(preparado[i + 1]);

        int novoX = mod26(aInv * x + bInv * y);
        int novoY = mod26(cInv * x + dInv * y);

        resultado += numeroParaLetra(novoX);
        resultado += numeroParaLetra(novoY);
    }

    return resultado;
}
std::string cifraVigenere(const std::string& texto, const std::string& chave) {
    std::string resultado = "";
    int chaveIndex = 0;
    for (char c : texto) {
        if (isalpha(c)) {
            char ch = toupper(chave[chaveIndex % chave.length()]) - 'A';
            resultado += (toupper(c) - 'A' + ch) % 26 + 'A';
            chaveIndex++;
        } else {
            resultado += c;
        }
    }
    return resultado;
}

std::string decifraVigenere(const std::string& texto, const std::string& chave) {
    std::string resultado = "";
    int chaveIndex = 0;
    for (char c : texto) {
        if (isalpha(c)) {
            char ch = toupper(chave[chaveIndex % chave.length()]) - 'A';
            resultado += (toupper(c) - 'A' - ch + 26) % 26 + 'A';
            chaveIndex++;
        } else {
            resultado += c;
        }
    }
    return resultado;
}
std::string cifraVernamHex(const std::string& texto, const std::string& chave) {
    std::ostringstream oss;
    for (size_t i = 0; i < texto.length(); ++i) {
        char c = texto[i];
        char k = chave[i % chave.length()];
        char x = c ^ k;
        oss << std::hex << std::setw(2) << std::setfill('0') << (static_cast<int>(x) & 0xFF);
    }
    return oss.str();
}


std::string hexParaBytes(const std::string& hex) {
    std::string resultado;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteHex = hex.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteHex, nullptr, 16));
        resultado += byte;
    }
    return resultado;
}

std::string decifraVernamHex(const std::string& hexCifrado, const std::string& chave) {
    std::string bytes = hexParaBytes(hexCifrado);
    std::string resultado;
    for (size_t i = 0; i < bytes.length(); ++i) {
        char x = bytes[i];
        char k = chave[i % chave.length()];
        resultado += x ^ k;
    }
    return resultado;
}
MainWindow::MainWindow(QWidget *parent)                 // Parte do código pra a interface, onde eu coloco o nome da janela, e faço a conexão dos botões com seus respsectivos códigos
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Cifras Clássicas - Criptografar e Descriptografar - Feito por Jean Arruda   ");
    ui->entradaChave2->setVisible(false);
    ui->labelChave2->setVisible(false);

    connect(ui->btnCifrar, &QPushButton::clicked, this, &MainWindow::acaoCifrar);
    connect(ui->btnDecifrar, &QPushButton::clicked, this, &MainWindow::acaoDecifrar);
    connect(ui->comboCifras, &QComboBox::currentTextChanged,
            this, &MainWindow::onComboCifrasChanged);

}

std::string cifraOTP(const std::string& texto, const std::string& chave) {
    std::string resultado = "";
    if (chave.length() != texto.length())
        return "Erro: a chave deve ter o mesmo tamanho do texto.";

    for (size_t i = 0; i < texto.length(); ++i) {
        if (isalpha(texto[i])) {
            char t = toupper(texto[i]) - 'A';
            char k = toupper(chave[i]) - 'A';
            char c = ((t + k) % 26) + 'A';
            resultado += c;
        } else {
            resultado += texto[i]; // mantém espaços e pontuação
        }
    }
    return resultado;
}

std::string decifraOTP(const std::string& texto, const std::string& chave) {
    std::string resultado = "";
    if (chave.length() != texto.length())
        return "Erro: a chave deve ter o mesmo tamanho do texto.";

    for (size_t i = 0; i < texto.length(); ++i) {
        if (isalpha(texto[i])) {
            char c = toupper(texto[i]) - 'A';
            char k = toupper(chave[i]) - 'A';
            char t = ((c - k + 26) % 26) + 'A';
            resultado += t;
        } else {
            resultado += texto[i];
        }
    }
    return resultado;
}

std::string cifraRailFence(const std::string& texto, int trilhos) {
    if (trilhos <= 1 || texto.empty()) return texto;

    std::vector<std::string> linhas(trilhos);
    int linha = 0;
    bool descendo = true;

    for (char c : texto) {
        linhas[linha] += c;

        if (descendo) {
            if (linha == trilhos - 1)
                descendo = false;
            else
                linha++;
        } else {
            if (linha == 0)
                descendo = true;
            else
                linha--;
        }
    }

    std::string resultado;
    for (const auto& l : linhas)
        resultado += l;

    return resultado;
}

std::string decifraRailFence(const std::string& texto, int trilhos) {
    if (trilhos <= 1 || texto.empty()) return texto;

    std::vector<std::vector<bool>> mapa(texto.length(), std::vector<bool>(trilhos, false));
    int linha = 0;
    bool descendo = true;

    // Primeiro passo: marcar posições
    for (size_t i = 0; i < texto.length(); ++i) {
        mapa[i][linha] = true;
        if (descendo) {
            if (linha == trilhos - 1)
                descendo = false;
            else
                linha++;
        } else {
            if (linha == 0)
                descendo = true;
            else
                linha--;
        }
    }

    // Preencher as letras nas posições marcadas
    std::vector<std::string> trilho(trilhos, std::string(texto.length(), '\0'));
    size_t idx = 0;
    for (int r = 0; r < trilhos; ++r) {
        for (size_t c = 0; c < texto.length(); ++c) {
            if (mapa[c][r]) {
                trilho[r][c] = texto[idx++];
            }
        }
    }

    // Reconstruir texto
    std::string resultado = "";
    linha = 0;
    descendo = true;
    for (size_t i = 0; i < texto.length(); ++i) {
        resultado += trilho[linha][i];
        if (descendo) {
            if (linha == trilhos - 1)
                descendo = false;
            else
                linha++;
        } else {
            if (linha == 0)
                descendo = true;
            else
                linha--;
        }
    }

    return resultado;
}

std::vector<int> ordemChave(const std::string& chave) {
    std::vector<std::pair<char, int>> letras;

    for (size_t i = 0; i < chave.length(); ++i)
        letras.emplace_back(chave[i], i);

    std::sort(letras.begin(), letras.end());

    std::vector<int> ordem(chave.length());
    for (size_t i = 0; i < letras.size(); ++i)
        ordem[i] = letras[i].second;

    return ordem;
}

std::string cifraColunas(const std::string& texto, const std::string& chave) {
    if (chave.empty()) return "Chave inválida.";

    int colunas = chave.length();
    int linhas = (texto.length() + colunas - 1) / colunas;

    std::vector<std::vector<char>> tabela(linhas, std::vector<char>(colunas, 'X'));

    for (size_t i = 0; i < texto.length(); ++i)
        tabela[i / colunas][i % colunas] = texto[i];

    std::vector<int> ordem = ordemChave(chave);
    std::string resultado;

    for (int idx : ordem) {
        for (int i = 0; i < linhas; ++i)
            resultado += tabela[i][idx];
    }

    return resultado;
}

std::string decifraColunas(const std::string& texto, const std::string& chave) {
    if (chave.empty()) return "Chave inválida.";

    int colunas = chave.length();
    int linhas = (texto.length() + colunas - 1) / colunas;
    int total = linhas * colunas;

    std::vector<std::vector<char>> tabela(linhas, std::vector<char>(colunas, 'X'));
    std::vector<int> ordem = ordemChave(chave);

    size_t index = 0;
    for (int idx : ordem) {
        for (int i = 0; i < linhas; ++i) {
            if (index < texto.length())
                tabela[i][idx] = texto[index++];
        }
    }

    std::string resultado;
    for (int i = 0; i < linhas; ++i)
        for (int j = 0; j < colunas; ++j)
            resultado += tabela[i][j];

    return resultado;
}

std::string cifraDuplaTransposicao(const std::string& texto, const std::string& chave1, const std::string& chave2) {
    // PRIMEIRA TRANSPOSTA
    int col1 = chave1.length();
    int lin1 = (texto.length() + col1 - 1) / col1;

    std::vector<std::vector<char>> matriz1(lin1, std::vector<char>(col1, 'X'));

    size_t idx = 0;
    for (int i = 0; i < lin1 && idx < texto.length(); ++i)
        for (int j = 0; j < col1 && idx < texto.length(); ++j)
            matriz1[i][j] = texto[idx++];

    std::vector<int> ordem1 = ordemChave(chave1);
    std::vector<std::vector<char>> transposta1(lin1, std::vector<char>(col1));

    for (int j = 0; j < col1; ++j)
        for (int i = 0; i < lin1; ++i)
            transposta1[i][j] = matriz1[i][ordem1[j]];

    // Gera string temporária
    std::string temp;
    for (int i = 0; i < lin1; ++i)
        for (int j = 0; j < col1; ++j)
            temp += transposta1[i][j];

    // SEGUNDA TRANSPOSTA
    int col2 = chave2.length();
    int lin2 = (temp.length() + col2 - 1) / col2;

    std::vector<std::vector<char>> matriz2(lin2, std::vector<char>(col2, 'X'));
    idx = 0;
    for (int i = 0; i < lin2 && idx < temp.length(); ++i)
        for (int j = 0; j < col2 && idx < temp.length(); ++j)
            matriz2[i][j] = temp[idx++];

    std::vector<int> ordem2 = ordemChave(chave2);
    std::vector<std::vector<char>> transposta2(lin2, std::vector<char>(col2));

    for (int j = 0; j < col2; ++j)
        for (int i = 0; i < lin2; ++i)
            transposta2[i][j] = matriz2[i][ordem2[j]];

    // Resultado final
    std::string resultado;
    for (int i = 0; i < lin2; ++i)
        for (int j = 0; j < col2; ++j)
            resultado += transposta2[i][j];

    return resultado;
}

std::string decifraDuplaTransposicao(const std::string& texto, const std::string& chave1, const std::string& chave2) {
    // INVERTE SEGUNDA TRANSPOSIÇÃO
    int col2 = chave2.length();
    int lin2 = (texto.length() + col2 - 1) / col2;

    std::vector<int> ordem2 = ordemChave(chave2);
    std::vector<std::vector<char>> matriz2(lin2, std::vector<char>(col2));

    size_t idx = 0;
    for (int j = 0; j < col2; ++j)
        for (int i = 0; i < lin2; ++i)
            if (idx < texto.length())
                matriz2[i][ordem2[j]] = texto[idx++];

    std::string temp;
    for (int i = 0; i < lin2; ++i)
        for (int j = 0; j < col2; ++j)
            temp += matriz2[i][j];

    // INVERTE PRIMEIRA TRANSPOSIÇÃO
    int col1 = chave1.length();
    int lin1 = (temp.length() + col1 - 1) / col1;

    std::vector<int> ordem1 = ordemChave(chave1);
    std::vector<std::vector<char>> matriz1(lin1, std::vector<char>(col1));

    idx = 0;
    for (int j = 0; j < col1; ++j)
        for (int i = 0; i < lin1; ++i)
            if (idx < temp.length())
                matriz1[i][ordem1[j]] = temp[idx++];

    std::string resultado;
    for (int i = 0; i < lin1; ++i)
        for (int j = 0; j < col1; ++j)
            resultado += matriz1[i][j];

    return resultado;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::acaoCifrar() {
    QString texto = ui->entradaTexto->text();
    QString cifraSelecionada = ui->comboCifras->currentText();

    std::string resultado;

    if (cifraSelecionada == "César") {
        bool ok;
        int chave = ui->entradaChave->text().toInt(&ok);
        if (!ok) {
            ui->resultadoLabel->setText("A chave deve ser um número inteiro.");
            return;
        }
        resultado = cifraCesar(texto.toStdString(), chave);

    } else if (cifraSelecionada == "Monoalfabética") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.length() != 26) {
            ui->resultadoLabel->setText("A chave deve conter 26 letras (sem repetição).");
            return;
        }
        resultado = cifraMonoalfabetica(texto.toStdString(), chave);

    } else if (cifraSelecionada == "Playfair") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para Playfair.");
            return;
        }
        resultado = cifraPlayfair(texto.toStdString(), chave, false);

    } else if (cifraSelecionada == "Hill (2x2)") {
        QStringList elementos = ui->entradaChave->text().split(' ');
        if (elementos.size() != 4) {
            ui->resultadoLabel->setText("Digite 4 números inteiros separados por espaço (ex: 3 3 2 5)");
            return;
        }

        int a = elementos[0].toInt();
        int b = elementos[1].toInt();
        int c = elementos[2].toInt();
        int d = elementos[3].toInt();

        resultado = cifraHill2x2(texto.toStdString(), a, b, c, d);
    }
    else if (cifraSelecionada == "Vigenere") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para Vigenère.");
            return;
        }
        resultado = cifraVigenere(texto.toStdString(), chave);
    }
    else if (cifraSelecionada == "Vernam") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para Vernam.");
            return;
        }
        resultado = cifraVernamHex(texto.toStdString(), chave);
    }

    else if (cifraSelecionada == "One-Time Pad") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para One-Time Pad.");
            return;
        }
        resultado = cifraOTP(texto.toStdString(), chave);
    }

    else if (cifraSelecionada == "Transposição (Rail Fence)") {
        bool ok;
        int trilhos = ui->entradaChave->text().toInt(&ok);
        if (!ok || trilhos <= 1) {
            ui->resultadoLabel->setText("A chave deve ser um número inteiro > 1 (número de trilhos).");
            return;
        }
        resultado = cifraRailFence(texto.toStdString(), trilhos);
    }

    else if (cifraSelecionada == "Transposição por Colunas") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave textual para transposição por colunas.");
            return;
        }
        resultado = cifraColunas(texto.toStdString(), chave);
    }

    else if (cifraSelecionada == "Dupla Transposição") {
    std::string chave1 = ui->entradaChave->text().toStdString();
    std::string chave2 = ui->entradaChave2->text().toStdString();

        if (chave1.empty() || chave2.empty()) {
            ui->resultadoLabel->setText("Preencha as duas chaves.");
            return;
        }

    resultado = cifraDuplaTransposicao(texto.toStdString(), chave1, chave2);
}


    ui->resultadoLabel->setText("Texto Cifrado: " + QString::fromStdString(resultado));
}

void MainWindow::acaoDecifrar() {
    QString texto = ui->entradaTexto->text();
    QString cifraSelecionada = ui->comboCifras->currentText();

    std::string resultado;

    if (cifraSelecionada == "César") {
        bool ok;
        int chave = ui->entradaChave->text().toInt(&ok);
        if (!ok) {
            ui->resultadoLabel->setText("A chave deve ser um número inteiro.");
            return;
        }
        resultado = decifraCesar(texto.toStdString(), chave);

    } else if (cifraSelecionada == "Monoalfabética") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.length() != 26) {
            ui->resultadoLabel->setText("A chave deve conter 26 letras (sem repetição).");
            return;
        }
        resultado = decifraMonoalfabetica(texto.toStdString(), chave);
    } else if (cifraSelecionada == "Playfair") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para Playfair.");
            return;
        }
        resultado = cifraPlayfair(texto.toStdString(), chave, true);
    }
    else if (cifraSelecionada == "Hill (2x2)") {
        QStringList elementos = ui->entradaChave->text().split(' ');
        if (elementos.size() != 4) {
            ui->resultadoLabel->setText("Digite 4 números inteiros separados por espaço (ex: 3 3 2 5)");
            return;
        }

        int a = elementos[0].toInt();
        int b = elementos[1].toInt();
        int c = elementos[2].toInt();
        int d = elementos[3].toInt();

        resultado = decifraHill2x2(texto.toStdString(), a, b, c, d);
    }
    else if (cifraSelecionada == "Vigenere") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para Vigenère.");
            return;
        }
        resultado = decifraVigenere(texto.toStdString(), chave);
    }
    else if (cifraSelecionada == "Vernam") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para Vernam.");
            return;
        }
        resultado = decifraVernamHex(texto.toStdString(), chave);
    }
    else if (cifraSelecionada == "One-Time Pad") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave para One-Time Pad.");
            return;
        }
        resultado = decifraOTP(texto.toStdString(), chave);
    }

    else if (cifraSelecionada == "Transposição (Rail Fence)") {
        bool ok;
        int trilhos = ui->entradaChave->text().toInt(&ok);
        if (!ok || trilhos <= 1) {
            ui->resultadoLabel->setText("A chave deve ser um número inteiro > 1 (número de trilhos).");
            return;
        }
        resultado = decifraRailFence(texto.toStdString(), trilhos);
    }

    else if (cifraSelecionada == "Transposição por Colunas") {
        std::string chave = ui->entradaChave->text().toStdString();
        if (chave.empty()) {
            ui->resultadoLabel->setText("Digite uma chave textual para transposição por colunas.");
            return;
        }
        resultado = decifraColunas(texto.toStdString(), chave);
    }

    else if (cifraSelecionada == "Dupla Transposição") {
    std::string chave1 = ui->entradaChave->text().toStdString();
    std::string chave2 = ui->entradaChave2->text().toStdString();

    if (chave1.empty() || chave2.empty()) {
        ui->resultadoLabel->setText("Preencha as duas chaves.");
        return;
    }

    resultado = decifraDuplaTransposicao(texto.toStdString(), chave1, chave2);
}
    ui->resultadoLabel->setText("Texto Decifrado: " + QString::fromStdString(resultado));
}

void MainWindow::onComboCifrasChanged(const QString &text) {
    if (text == "César") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Chave numérica:");
        ui->entradaChave->setPlaceholderText("Ex: 3");
        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("A cifra de César usa uma chave numérica para deslocar as letras.");
        ui->labelAviso->setVisible(true);

        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    } else if (text == "Monoalfabética") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Chave (26 letras):");
        ui->entradaChave->setPlaceholderText("Ex: QWERTYUIOPASDFGHJKLZXCVBNM");
        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("Cada letra do alfabeto é substituída por outra da chave.");
        ui->labelAviso->setVisible(true);

        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    } else if (text == "Playfair") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Chave (texto qualquer):");
        ui->entradaChave->setPlaceholderText("Ex: EXEMPLO");
        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("A cifra Playfair converte 'J' para 'I' e adiciona 'X' em textos com número ímpar de letras.");
        ui->labelAviso->setVisible(true);

        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    } else if (text == "Hill (2x2)") {
    ui->entradaChave->setVisible(true);
    ui->labelChave->setText("Chave (4 números):");
    ui->entradaChave->setPlaceholderText("Ex: 3 3 2 5");

    ui->btnCifrar->setText("Cifrar");
    ui->btnDecifrar->setText("Decifrar");

    ui->labelAviso->setText("Aviso: Texto será ajustado para tamanho par. Apenas letras A-Z são consideradas.");
    ui->labelAviso->setVisible(true);
    ui->entradaChave2->setVisible(false);
    ui->labelChave2->setVisible(false);

    } else if (text == "Vigenere") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Chave (texto):");
        ui->entradaChave->setPlaceholderText("Ex: SEGURANCA");

        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("Aviso: Apenas letras A-Z são utilizadas. Ignore espaços e pontuação.");
        ui->labelAviso->setVisible(true);
        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    }
    else if (text == "Vernam") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Chave (texto):");
        ui->entradaChave->setPlaceholderText("Ex: SEGREDO");

        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("A cifra de Vernam usa XOR.");
        ui->labelAviso->setVisible(true);
        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    }
    else if (text == "One-Time Pad") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Chave (mesmo tamanho do texto):");
        ui->entradaChave->setPlaceholderText("Ex: XMCKLZ");

        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("A cifra One-Time Pad exige chave do mesmo tamanho do texto. Usa apenas letras A-Z.");
        ui->labelAviso->setVisible(true);
        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    }

    else if (text == "Transposição (Rail Fence)") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Número de trilhos:");
        ui->entradaChave->setPlaceholderText("Ex: 3");

        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("A cifra Rail Fence reorganiza as letras em padrão de zigue-zague.");
        ui->labelAviso->setVisible(true);
        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    }

    else if (text == "Transposição por Colunas") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Chave (texto):");
        ui->entradaChave->setPlaceholderText("Ex: CABE");

        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("A cifra reorganiza o texto em colunas com base na ordem alfabética da chave.");
        ui->labelAviso->setVisible(true);
        ui->entradaChave2->setVisible(false);
        ui->labelChave2->setVisible(false);

    }
    else if (text == "Dupla Transposição") {
        ui->entradaChave->setVisible(true);
        ui->labelChave->setText("Primeira chave:");
        ui->entradaChave->setPlaceholderText("Ex: CABE");

        ui->entradaChave2->setVisible(true);
        ui->labelChave2->setVisible(true);
        ui->labelChave2->setText("Segunda chave:");
        ui->entradaChave2->setPlaceholderText("Ex: DCBA");

        ui->btnCifrar->setText("Cifrar");
        ui->btnDecifrar->setText("Decifrar");

        ui->labelAviso->setText("Use duas chaves para aplicar transposição dupla.");
        ui->labelAviso->setVisible(true);
    }



}



