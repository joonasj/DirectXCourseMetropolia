#ifndef _BASE_CLASS_H
#define _BASE_CALSS_H

#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>



class DxBaseClass {

public:
	DxBaseClass();
	virtual ~DxBaseClass();
	bool Initialize( HINSTANCE hInstance, HWND hwnd);

	void Shutdown();

	virtual bool loadContent();
	virtual void UnLoadContent();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

protected:
	HINSTANCE hInstance_;
	HWND hwnd_;
	D3D_DRIVER_TYPE driverType_;
	D3D_FEATURE_LEVEL featureLevel_;

	ID3D11Device* d3dDevice_;
	ID3D11DeviceContext* d3dContext_;
	IDXGISwapChain* swapChain_;
	ID3D11RenderTargetView* backBufferTarget_;

};

#endif