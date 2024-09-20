from fastapi import FastAPI, Request
from fastapi.middleware.cors import CORSMiddleware

app = FastAPI()

app.add_middleware(
    middleware_class=CORSMiddleware,
    allow_origins=["https://ui.mypage.com"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/test_cors")
def test_cors(request: Request):
    print(request)


if __name__ == "__main__":
    import uvicorn
    uvicorn.run("cors_example:app", reload=True)