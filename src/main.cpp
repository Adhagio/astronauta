#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

using namespace std;

struct Astronauta {
    string cpf, nome;
    int idade;
    bool vivo = true, disponivel = true;
    Astronauta(string c, string n, int i) : cpf(c), nome(n), idade(i) {}
    void embarcar() { disponivel = false; }
    void desembarcar() { if (vivo) disponivel = true; }
    void morrer() { vivo = false; disponivel = false; }
};

struct Voo {
    int codigo;
    string estado = "planejado";
    vector<string> cpfs;
    Voo(int c) : codigo(c) {}
    bool tem(string c) {
        for (auto &x : cpfs) if (x == c) return true;
        return false;
    }
    bool remover(string c) {
        for (int i = 0; i < (int)cpfs.size(); i++)
            if (cpfs[i] == c) { cpfs.erase(cpfs.begin() + i); return true; }
        return false;
    }
};

struct Agencia {
    vector<Astronauta> astros;
    vector<Voo> voos;

    int achaA(string c) {
        for (int i = 0; i < (int)astros.size(); i++)
            if (astros[i].cpf == c) return i;
        return -1;
    }
    int achaV(int c) {
        for (int i = 0; i < (int)voos.size(); i++)
            if (voos[i].codigo == c) return i;
        return -1;
    }
    int vooPlanejado(int codigo) {
        int v = achaV(codigo);
        if (v == -1) { cout << "ERRO: voo " << codigo << " nao cadastrado\n"; return -1; }
        if (voos[v].estado != "planejado") { cout << "ERRO: voo " << codigo << " nao esta planejado\n"; return -1; }
        return v;
    }

    void cadastrarAstronauta(string cpf, string nome, int idade) {
        if (achaA(cpf) != -1) { cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado\n"; return; }
        astros.push_back(Astronauta(cpf, nome, idade));
        cout << "OK: astronauta " << cpf << " cadastrado\n";
    }
    void cadastrarVoo(int codigo) {
        if (achaV(codigo) != -1) { cout << "ERRO: voo " << codigo << " ja cadastrado\n"; return; }
        voos.push_back(Voo(codigo));
        cout << "OK: voo " << codigo << " cadastrado\n";
    }
    void adicionarAstronauta(string cpf, int codigo) {
        int a = achaA(cpf);
        if (a == -1) { cout << "ERRO: astronauta " << cpf << " nao cadastrado\n"; return; }
        int v = vooPlanejado(codigo);
        if (v == -1) return;
        if (!astros[a].vivo) { cout << "ERRO: astronauta " << cpf << " esta morto\n"; return; }
        if (voos[v].tem(cpf)) { cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << "\n"; return; }
        voos[v].cpfs.push_back(cpf);
        cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << "\n";
    }
    void removerAstronauta(string cpf, int codigo) {
        if (achaA(cpf) == -1) { cout << "ERRO: astronauta " << cpf << " nao cadastrado\n"; return; }
        int v = vooPlanejado(codigo);
        if (v == -1) return;
        if (!voos[v].remover(cpf)) { cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << "\n"; return; }
        cout << "OK: astronauta " << cpf << " removido do voo " << codigo << "\n";
    }
    void lancarVoo(int codigo) {
        int v = vooPlanejado(codigo);
        if (v == -1) return;
        if (voos[v].cpfs.empty()) { cout << "ERRO: voo " << codigo << " nao possui astronautas\n"; return; }
        for (auto &c : voos[v].cpfs) {
            int a = achaA(c);
            if (!astros[a].vivo) { cout << "ERRO: astronauta " << c << " esta morto\n"; return; }
            if (!astros[a].disponivel) { cout << "ERRO: astronauta " << c << " esta indisponivel\n"; return; }
        }
        for (auto &c : voos[v].cpfs) astros[achaA(c)].embarcar();
        voos[v].estado = "em curso";
        cout << "OK: voo " << codigo << " lancado\n";
    }
    void explodirVoo(int codigo) {
        int v = achaV(codigo);
        if (v == -1) { cout << "ERRO: voo " << codigo << " nao cadastrado\n"; return; }
        if (voos[v].estado != "em curso") { cout << "ERRO: voo " << codigo << " nao esta em curso\n"; return; }
        for (auto &c : voos[v].cpfs) astros[achaA(c)].morrer();
        voos[v].estado = "finalizado com explosao";
        cout << "OK: voo " << codigo << " explodiu\n";
    }
    void finalizarVoo(int codigo) {
        int v = achaV(codigo);
        if (v == -1) { cout << "ERRO: voo " << codigo << " nao cadastrado\n"; return; }
        if (voos[v].estado != "em curso") { cout << "ERRO: voo " << codigo << " nao esta em curso\n"; return; }
        for (auto &c : voos[v].cpfs) astros[achaA(c)].desembarcar();
        voos[v].estado = "finalizado com sucesso";
        cout << "OK: voo " << codigo << " finalizado com sucesso\n";
    }
    void listarVoos() {
        cout << "LISTA DE VOOS\n";
        string ests[] = {"planejado", "em curso", "finalizado com sucesso", "finalizado com explosao"};
        for (auto &e : ests) {
            cout << "== " << e << " ==\n";
            bool achou = false;
            for (auto &v : voos) {
                if (v.estado != e) continue;
                achou = true;
                cout << "Voo " << v.codigo << ": ";
                if (v.cpfs.empty()) cout << "sem astronautas\n";
                else {
                    for (int i = 0; i < (int)v.cpfs.size(); i++) {
                        if (i) cout << ", ";
                        cout << v.cpfs[i] << " " << astros[achaA(v.cpfs[i])].nome;
                    }
                    cout << "\n";
                }
            }
            if (!achou) cout << "(nenhum)\n";
        }
    }
    void listarMortos() {
        cout << "ASTRONAUTAS MORTOS\n";
        bool achou = false;
        for (auto &a : astros) {
            if (a.vivo) continue;
            achou = true;
            cout << a.cpf << " " << a.nome << " - voos:";
            bool voou = false;
            for (auto &v : voos)
                if (v.estado != "planejado" && v.tem(a.cpf)) { cout << " " << v.codigo; voou = true; }
            if (!voou) cout << " nenhum";
            cout << "\n";
        }
        if (!achou) cout << "(nenhum)\n";
    }
    void listarAstronautas() {
        cout << "LISTA DE ASTRONAUTAS\n";
        cout << "== disponiveis ==\n";
        bool achou = false;
        for (auto &a : astros)
            if (a.vivo && a.disponivel) {
                achou = true;
                cout << a.cpf << " " << a.nome << " (" << a.idade << " anos)\n";
            }
        if (!achou) cout << "(nenhum)\n";
        cout << "== em voo ==\n";
        achou = false;
        for (auto &a : astros)
            if (a.vivo && !a.disponivel) {
                achou = true;
                cout << a.cpf << " " << a.nome << " (" << a.idade << " anos)";
                for (auto &v : voos)
                    if (v.estado == "em curso" && v.tem(a.cpf)) { cout << " - voo " << v.codigo; break; }
                cout << "\n";
            }
        if (!achou) cout << "(nenhum)\n";
        cout << "== mortos ==\n";
        achou = false;
        for (auto &a : astros)
            if (!a.vivo) {
                achou = true;
                cout << a.cpf << " " << a.nome << " (" << a.idade << " anos)\n";
            }
        if (!achou) cout << "(nenhum)\n";
    }
    void historico(string cpf) {
        int a = achaA(cpf);
        if (a == -1) { cout << "ERRO: astronauta " << cpf << " nao cadastrado\n"; return; }
        cout << "HISTORICO DE " << astros[a].cpf << " " << astros[a].nome << "\n";
        bool achou = false;
        for (auto &v : voos)
            if (v.estado != "planejado" && v.tem(cpf)) {
                achou = true;
                cout << "voo " << v.codigo << ": " << v.estado << "\n";
            }
        if (!achou) cout << "(nenhum voo)\n";
    }
    void salvar(string arquivo) {
        ofstream saida(arquivo);
        if (!saida.is_open()) {
            cout << "ERRO: nao foi possivel salvar em " << arquivo << "\n";
            return;
        }
        for (auto &a : astros)
            saida << "A;" << a.cpf << ";" << a.nome << ";" << a.idade << ";"
                  << a.vivo << ";" << a.disponivel << "\n";
        for (auto &v : voos) {
            saida << "V;" << v.codigo << ";" << v.estado << ";";
            for (int i = 0; i < (int)v.cpfs.size(); i++) {
                if (i) saida << ",";
                saida << v.cpfs[i];
            }
            saida << "\n";
        }
        cout << "OK: dados salvos em " << arquivo << "\n";
    }
    void carregar(string arquivo) {
        ifstream entrada(arquivo);
        if (!entrada.is_open()) {
            cout << "ERRO: nao foi possivel carregar de " << arquivo << "\n";
            return;
        }
        vector<Astronauta> novosAstros;
        vector<Voo> novosVoos;
        string linha;
        while (getline(entrada, linha)) {
            if (!linha.empty() && linha[linha.size() - 1] == '\r')
                linha.erase(linha.size() - 1);
            if (linha.empty()) continue;
            stringstream ss(linha);
            vector<string> campos;
            string campo;
            while (getline(ss, campo, ';')) campos.push_back(campo);
            if (campos[0] == "A" && (int)campos.size() >= 6) {
                Astronauta a(campos[1], campos[2], stoi(campos[3]));
                a.vivo = campos[4] == "1";
                a.disponivel = campos[5] == "1";
                novosAstros.push_back(a);
            } else if (campos[0] == "V" && (int)campos.size() >= 3) {
                Voo v(stoi(campos[1]));
                v.estado = campos[2];
                if ((int)campos.size() >= 4) {
                    stringstream lista(campos[3]);
                    string cpf;
                    while (getline(lista, cpf, ',')) if (!cpf.empty()) v.cpfs.push_back(cpf);
                }
                novosVoos.push_back(v);
            }
        }
        astros = novosAstros;
        voos = novosVoos;
        cout << "OK: dados carregados de " << arquivo << "\n";
    }
};

int main() {
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    Agencia agencia;
    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);
            agencia.cadastrarAstronauta(cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.cadastrarVoo(codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.adicionarAstronauta(cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.removerAstronauta(cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.lancarVoo(codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.explodirVoo(codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.finalizarVoo(codigo);
        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();
        } else if (comando == "LISTAR_ASTRONAUTAS") {
            agencia.listarAstronautas();
        } else if (comando == "HISTORICO") {
            string cpf;
            cin >> cpf;
            agencia.historico(cpf);
        } else if (comando == "SALVAR") {
            string arquivo;
            cin >> arquivo;
            agencia.salvar(arquivo);
        } else if (comando == "CARREGAR") {
            string arquivo;
            cin >> arquivo;
            agencia.carregar(arquivo);
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}