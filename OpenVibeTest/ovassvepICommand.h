#ifndef __OpenViBEApplication_ICommand_H__
#define __OpenViBEApplication_ICommand_H__




	class ICommand
	{
		public:
			ICommand(){};

			virtual ~ICommand() {};

			virtual void processFrame() = 0;
	};




#endif // __OpenViBEApplication_ICommand_H__
