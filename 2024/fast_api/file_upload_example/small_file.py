from fastapi import File, APIRouter
from fastapi.responses import FileResponse

router = APIRouter(prefix="/small")

@router.post("/upload")
async def upload_small_file(small_file: bytes = File()) -> str:
    return f"file size : {len(small_file)}"

# File : Fast API에서는 파일을 기본적으로 청크 단위로 가져와서 메모리 단에서 재조립
# 따라서 작은 크기 파일에서만 File 함수로 파일 가져와야 함

@router.get("/download")
async def download_small_file(name: str):
    return FileResponse(name)

# FileResponse : 파일에 대한 응답을 한 번에 처리
# 작은 파일에 대해서만 사용 권고
