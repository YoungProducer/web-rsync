type FilesMap = {
  [prop: string]: string;
}

type ActionUnionType = 'REMOVE' | 'UPDATE' | 'ADD';

type FileAction = {
  path: string;
  type: ActionUnionType;
}

export declare type sha256_checksum = (path: string) => string;

export declare type scanDir = (path: string) => FilesMap;

export declare type getFoldersDiff = (path: string, next: FilesMap) => FileAction[]; 