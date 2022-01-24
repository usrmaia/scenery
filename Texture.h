class Texture{
    private:
        int width, height, canals;
        unsigned char *date;
        unsigned int id;
    public:
        void load(const char *file_path);
        unsigned int get_id();
};