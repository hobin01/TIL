import glob
import boto3
import botocore
import os

def make_bucket(region, PROFILE_NAME, BUCKET_NAME):
    session = boto3.Session(profile_name = PROFILE_NAME)
    location = {'LocationConstraint' : region}
    s3 = session.client('s3', region_name = region)
    s3.create_bucket(Bucket = BUCKET_NAME, CreateBucketConfiguration = location)

    print("bucket %s create success" %(BUCKET_NAME))
    return 

def upload_files(region, PROFILE_NAME, BUCKET_NAME, FORDER_NAME, FILE_PATH):
    session = boto3.Session(profile_name = PROFILE_NAME)
    s3 = session.client('s3', region_name = region)
    files = glob.glob(FILE_PATH)

    for filename in files:
        key_file = "%s/%s" %(FORDER_NAME, os.path.basename(filename))
        s3.upload_file(filename, BUCKET_NAME, key_file)
    
    print("upload files in %s to %s success" %(FILE_PATH, BUCKET_NAME))

    return

def delete_all_files(region, PROFILE_NAME, BUCKET_NAME):
    session = boto3.Session(profile_name = PROFILE_NAME)
    s3 = session.client('s3', region_name = region)

    for key in s3.list_objects(Bucket = BUCKET_NAME)['Contents'] :
        s3.delete_object(Bucket = BUCKET_NAME, Key = key['Key'])
    
    print("all files delete in %s" %(BUCKET_NAME))

    return
    
def delete_bucket(region, PROFILE_NAME, BUCKET_NAME):
    session = boto3.Session(profile_name = PROFILE_NAME)
    s3 = session.client('s3', region_name = region)
    s3.delete_bucket(Bucket = BUCKET_NAME)

    print("%s delete success" %(BUCKET_NAME))

    return


if __name__ == "__main__":
    region = 'ap-northeast-2'
    PROFILE_NAME = 'bob10-xxxx' # my aws profile
    BUCKET_NAME = 'bob10-xxxx-hw3' # my bucket name
    FORDER_NAME = 'hw3-dir' # directory in bucket
    FILE_PATH = './test_dir/*' # file path in local what uploaded

    make_bucket(region, PROFILE_NAME, BUCKET_NAME)
    upload_files(region, PROFILE_NAME, BUCKET_NAME, FORDER_NAME, FILE_PATH)
    delete_all_files(region, PROFILE_NAME, BUCKET_NAME)
    delete_bucket(region, PROFILE_NAME, BUCKET_NAME)
