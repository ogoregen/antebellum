
#pragma once

class texture{

	private:
		unsigned int slot;
		unsigned int ID;
		static unsigned int usedslots;

	public:
		texture(const char* path);
		~texture();
		void bind();
		void unbind();
};
