#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;


class Tweet; 

class Usuario {
public:
    string nomeUsuario;
    string nome;
    vector<Tweet> tweets;
    vector<Usuario*> seguidores;
    vector<Usuario*> seguindo;

    Usuario(const string& _nomeDoUsuario, const string& _nomeReal)
        : nomeUsuario(_nomeDoUsuario), nome(_nomeReal) {}

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
//implementar
};

void Usuario::postarTweet(const string& _conteudo) {
    //implementar
}

void Usuario::seguir(Usuario* _usuario) {
   //implementar
}

vector<Tweet> Usuario::receberFeed() const {
    //implementar
}



int main() {
    //implementar
    

    return 0;
}
