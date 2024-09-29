from fastapi import UploadFile, APIRouter

from fastapi.responses import StreamingResponse
from typing import Generator


router = APIRouter(prefix="/large")

@router.post("/upload")
async def upload_large_file(large_file: UploadFile) -> str:
    return f"file size : {large_file.size}, file name : {large_file.filename}"

# UploadFile : 대용량 파일 업로드 시 사용
# 서버 디스크에 SpooledTemporaryFile 객체 생성 후
# 제한된 메모리까지만 메모리로 파일 처리 후 나머지는 디스크에서 처리

def gen_file(path: str) -> Generator:
    with open(file=path, mode="rb") as file :
        yield file.read()

@router.get("/download")
async def download_large_file(name: str):
    gen_expr = gen_file(path=name)
    resp = StreamingResponse(content=gen_expr, status_code=200)
    return resp

# StreamingResponse : stream 형식으로 파일에 대한 응답 처리
# arg인 content 값에 대해 iteration하면서 파일을 청크 단위로 처리
# 큰 파일 처리에 적합
