from fastapi import FastAPI
import uvicorn

import small_file, large_file

app = FastAPI()
app.include_router(small_file.router)
app.include_router(large_file.router)

if __name__ == "__main__":
    uvicorn.run("main:app", reload=True)

# test files : https://myjob.page/tools/test-files