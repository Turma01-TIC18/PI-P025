#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

class Tweet; 

class Usuario {
public:
    string nomeUsuario;
    string nome;
    vector<Tweet> tweets;
    vector<Usuario*> seguidores;
    vector<Usuario*> seguindo;

    Usuario(const string& _nomeDoUsuario, const string& _nomeReal){
        nomeUsuario = _nomeDoUsuario;
        nome = _nomeReal;
    
    }

    const string& getNomeUsuario() const {
        return nomeUsuario;
    }

    const string& getNomeReal() const {
        return nome;
    }

    void postarTweet(const string& _conteudo);

    void seguir(Usuario* _usuario);

    vector<Tweet> receberFeed() const;
};

class Tweet {
public:
    Usuario* autor;
    string conteudo;
    string data_criacao;

    Tweet(Usuario* _autor, const string& _conteudo)
        : autor(_autor), conteudo(_conteudo) {
        time_t agora = time(0);
        data_criacao = ctime(&agora);
    }

    Usuario* getAutor() const {
        return autor;
    }

    const string& getConteudo() const {
        return conteudo;
    }

    const string& getDataCriacao() const {
        return data_criacao;
    }
};

class RedeSocial {
public:
    vector<Usuario> usuarios;

    void registrarUsuario(const string& _nomeDoUsuario, const string& _nomeReal) {
        usuarios.push_back(Usuario(_nomeDoUsuario, _nomeReal));
    }

    Usuario* buscarUsuario(const string& _nomeDoUsuario) {
        for (Usuario& usuario : usuarios) {
            if (usuario.getNomeUsuario() == _nomeDoUsuario) {
                return &usuario;
            }
        }
        return nullptr;
    }

    vector<Usuario> listarUsuarios() const {
        return usuarios;
    }

    vector<Tweet> listarTweets() const {
        vector<Tweet> allTweets;
        for (const Usuario& usuario : usuarios) {
            allTweets.insert(allTweets.end(), usuario.receberFeed().begin(), usuario.receberFeed().end());
        }
        return allTweets;
    }
};


void Usuario::postarTweet(const string& _conteudo) {
    Tweet tweet(this, _conteudo);
    tweets.push_back(tweet);
}

void Usuario::seguir(Usuario* _usuario) {
    if (_usuario != this) {
        seguindo.push_back(_usuario);
        _usuario->seguidores.push_back(this);
    }
}

vector<Tweet> Usuario::receberFeed() const {
    vector<Tweet> feed;
    for (Usuario* seguido : seguindo) {
        feed.insert(feed.end(), seguido->tweets.begin(), seguido->tweets.end());
    }
    sort(feed.rbegin(), feed.rend(), [](const Tweet& a, const Tweet& b) {
            return a.getDataCriacao() > b.getDataCriacao();
    });
    return feed;
}



int main() {
    RedeSocial redeSocial;
    int opcao = 0;
    bool sair = true;
    string nomeDoUsuario, nomeReal;
    string nomeDoSeguidor, nomeSeguindo;
    string nomeFeed;
    string nomeDoUsuarioDaPostagem, conteudo;
    Usuario* autor = redeSocial.buscarUsuario(nomeDoUsuarioDaPostagem);
    Usuario* seguidor = redeSocial.buscarUsuario(nomeDoSeguidor);
    Usuario* seguindo = redeSocial.buscarUsuario(nomeSeguindo);
    Usuario* usuarioFeed = redeSocial.buscarUsuario(nomeFeed);


    while (sair) {
        cout << "Rede Social\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Postar Tweet\n";
        cout << "3. Seguir usuario\n";
        cout << "4. Exibir Feed\n";
        cout << "5. Listar Usuarios\n";
        cout << "6. Listar Tweets\n";
        cout << "7. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cout << "Digite o nome de usuario: ";
            getline(cin >> ws, nomeDoUsuario);
            cout << "Digite o nome real: ";
            getline(cin >> ws, nomeReal);
            redeSocial.registrarUsuario(nomeDoUsuario, nomeReal);
            cout << "Usuário registrado com sucesso!\n";
            break;
        case 2:
            cout << "Digite o nome de usuário que deseja postar um Tweet: ";
            getline(cin >> ws, nomeDoUsuarioDaPostagem);
            autor = redeSocial.buscarUsuario(nomeDoUsuarioDaPostagem);

            if (autor) {
                cout << "Digite o conteúdo do Tweet: ";
                getline(cin >> ws, conteudo);
                autor->postarTweet(conteudo);
                cout << "Tweet postado com sucesso!\n";
            }
            else {
                cout << "Usuario não encontrado.\n";
            }
            break;
        case 3:
            cout << "Digite o nome de usuário seguidor: ";
            getline(cin >> ws, nomeDoSeguidor);
            seguidor = redeSocial.buscarUsuario(nomeDoSeguidor);
            if (seguidor) {
                cout << "Digite o nome de usuario que deseja seguir: ";
                getline(cin >> ws, nomeSeguindo);
                seguindo = redeSocial.buscarUsuario(nomeSeguindo);
                if (seguindo) {
                    seguidor->seguir(seguindo);
                    cout << nomeDoSeguidor << " está seguindo " << nomeSeguindo << ".\n";
                }
                else {
                    cout << "Usuário a ser seguido não encontrado.\n";
                }
            }
            else {
                cout << "Usuario seguidor nao encontrado.\n";
            }
            break;

        case 4:
            cout << "Digite o nome de usuario para exibir o feed: ";
            cin >> nomeFeed;
            usuarioFeed = redeSocial.buscarUsuario(nomeFeed);
            if (usuarioFeed) {
                vector<Tweet> feed = usuarioFeed->receberFeed();
                cout << "Feed de " << nomeFeed << ":\n";
                for (const Tweet& tweet : feed) {
                    cout << tweet.getAutor()->getNomeUsuario() << " (" << tweet.getDataCriacao() << "): " << tweet.getConteudo() << "\n";
                    system("pause");
                }
            }
            else {
                cout << "Usuario nao encontrado.\n";
            }
            break;

        case 5:

            cout << "Lista de Usuarios:\n";
            for (const Usuario& usuario : redeSocial.listarUsuarios()) {
                cout << "Nome de Usuário: " << usuario.getNomeUsuario() << ", Nome Real: " << usuario.getNomeReal() << "\n";
                system("pause");
            }
            break;
            

        case 6:
            cout << "Lista de Tweets:\n";
            for (const Usuario& usuario : redeSocial.listarUsuarios()) {
                for (const Tweet& tweet : usuario.tweets) {
                    cout << tweet.getAutor()->getNomeUsuario() << " (" << tweet.getDataCriacao() << "): " << tweet.getConteudo() << "\n";
                    system("pause");
                }
            }
            break;
        case 7:
            sair = false;
            break;

        default:

            cout << "Opcao invalida. Tente novamente.\n";
            break;
        }
    };
    return 0;
}