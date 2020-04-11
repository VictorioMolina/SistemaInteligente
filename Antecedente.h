using namespace std;

class Antecedente {
public:
    // Constructor/Destrcutor
    Antecedente(string nombre, string valor);
    ~Antecedente(){};

    // Metodos Set/Get
    void setNombre(string nombre);
    string getNombre();
    void setValor(string valor);
    string getValor();

private:
    string nombre;
    string valor;
};

