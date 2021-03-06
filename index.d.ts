export type FilesMap = {
  [prop: string]: string;
};

export type ActionUnionType = "REMOVE" | "UPDATE" | "ADD";

export type FileAction = {
  path: string;
  type: ActionUnionType;
};

export declare function sha256_checksum(path: string): string;

export declare function scanDir(path: string): FilesMap;

export declare function getFoldersDiff(
  path: string,
  path: string
): FileAction[];
export declare function getFoldersDiff(
  path: string,
  next: FilesMap
): FileAction[];
export declare function getFoldersDiff(
  path: FilesMap,
  next: FilesMap
): FileAction[];
