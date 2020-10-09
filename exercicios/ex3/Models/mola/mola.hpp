class Mola {
    private:
        float coef; // coeficiente de elasticidade (N/m)
    public:
        Mola(float coef1);
        ~Mola();
        void setCoef(float coef1);
        float getCoef();
};