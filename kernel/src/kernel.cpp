extern int a();
extern "C" int _start()
{
	return a();
}