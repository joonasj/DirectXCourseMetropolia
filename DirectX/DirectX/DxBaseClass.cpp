#include "DxBaseClass.h"

DxBaseClass::DxBaseClass():driverType_(D3D_DRIVER_TYPE_NULL ), featureLevel_(D3D_FEATURE_LEVEL_11_0), d3dDevice_(0), swapChain_(0), backBufferTarget_(0){
	
}

DxBaseClass::~DxBaseClass(){
	Shutdown();
}

bool DxBaseClass::Initialize( HINSTANCE hInstance, HWND hwnd){
	hInstance_ = hInstance;
	hwnd_ = hwnd;
	RECT dimensions;
	GetClientRect(hwnd, &dimensions);
	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
	};

	unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned creationFlags = 0;

#ifdef _DEBUG
	creationFlags != D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result;
	unsigned int driver = 0;

	for(driver = 0; driver < totalDriverTypes; ++driver){
		result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0, creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &swapChain_, &d3dDevice_, &featureLevel_, &d3dContext_);

		if(SUCCEEDED(result)){
			driverType_ = driverTypes[driver];
		}
	}

	if (FAILED(result)){
		DXTRACE_MSG("Failed to create the DirectX3D device");
		return false;
	}

	ID3D11Texture2D* backBufferTexture;
	result = swapChain_->GetBuffer(0, _uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

	if(FAILED(result)){
		DXTRACE_MSG("Failed for reason");
		return false;
	}

	result = d3dDevice_->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget_);

	if(backBufferTexture){
		backBufferTexture->Release();

	}

	if(FAILED(result)){
		DXTRACE_MSG("Failed for another reason");
		return false;
	}

	d3dContext_->OMSetRenderTargets(1, &backBufferTarget_, 0);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);

	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	d3dContext_->RSSetViewports(1, &viewport);

	return loadContent();

}

bool DxBaseClass::loadContent(){
	
}

bool DxBaseClass::UnLoadContent(){
	
}

void DxBaseClass::Shutdown(){
	UnLoadContent();

	if(backBufferTarget_) backBufferTarget_->Release();
	if(swapChain_) swapChain_->Release();
	if(d3dContext_) d3dContext_->Release();
	if(d3dDevice_) d3dDevice_->Release();

	backBufferTarget_ = 0;
	swapChain_ = 0;
	d3dContext_ = 0;
	d3dDevice_ = 0;
}