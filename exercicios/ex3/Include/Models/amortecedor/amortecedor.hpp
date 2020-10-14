class Amortecedor {
    private:
        float coef; // coeficiente de amortecimento (N.s/m)
    public:
        Amortecedor(float coef1);
        ~Amortecedor();
        void setCoef(float coef1);
        float getCoef();
};