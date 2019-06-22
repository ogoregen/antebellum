
class texture{

	private:
		unsigned int ID;

	public:
		texture(const char* path);
		~texture();
		void bind(unsigned int slot);
		void unbind();
};
