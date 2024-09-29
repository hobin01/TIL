from fastapi import FastAPI
from web import creature, explorer, game

app = FastAPI()
app.include_router(explorer.router)
app.include_router(creature.router)
app.include_router(game.router)

# post를 options로 인식 : cors 설정 진행 
from fastapi.middleware.cors import CORSMiddleware

# CORS 설정 추가
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # 웹 애플리케이션이 실행되는 주소를 허용
    allow_credentials=True,
    allow_methods=["*"],  # 모든 HTTP 메서드를 허용
    allow_headers=["*"],  # 모든 헤더를 허용
)

if __name__ == "__main__":
    import uvicorn

    uvicorn.run("main:app", reload=True)
