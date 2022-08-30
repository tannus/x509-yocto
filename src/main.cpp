#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

using std::cout;
using std::endl;

int main(int argc, char** argv){
	
	//Variable declaration
	X509* certificado;
	int tamanhoCertificado;
	char* nomeBuffer;
	unsigned char *buffer;
	const unsigned char* dadosCertificado;
	std::string dados;
	std::ofstream arquivoEntrada;
	std::ostringstream stringStream;

	//Opens cert file given the input line
	if(!argv[1]){
		cout << "Certificado nao foi incluido" << endl;
		return 0;
	}
	arquivoEntrada.open(argv[1]);
	
    //Parses the file into a string
    if(!arquivoEntrada){
    	cout << "Erro na abertura do arquivo" << endl;
		arquivoEntrada.close();
		return 0;              
	}
	stringStream << arquivoEntrada.rdbuf();
	dados = stringStream.str();
	std::copy(dados.cbegin(), dados.cend(), buffer);

	//Lê o certificado da memória
    dadosCertificado = buffer;
	certificado = d2i_X509(NULL, &dadosCertificado, tamanhoCertificado);
	if(certificado == NULL){
		cout << "Erro na leitura do arquivo" << endl;
		arquivoEntrada.close();
		return 0;
	}

	//Reads certificate name from memory
	X509_NAME* subject = X509_get_subject_name(certificado);

	//Obtains ASCII representation fro X509_NAME
	X509_NAME_oneline(subject, nomeBuffer, tamanhoCertificado);
                          

    //Closes the input file
	arquivoEntrada.close();

	return 0;
}
