import sys
import time
import subprocess
import os
import shutil

# import ...

# --- 設定 ---
# 監視対象の拡張子 (main_task.c とその依存ファイル)
WATCH_EXTENSIONS = ("Makefile", ".cpp", ".hpp")
# 実行ファイル名
EXECUTABLE = "MyLang.exe"
# ビルドコマンド
BUILD_CMD = [r"C:\msys64\mingw64\bin\mingw32-make.exe"]


def get_file_mtime(filepath):
    """ファイルの最終更新時刻を取得する"""
    try:
        return os.stat(filepath).st_mtime
    except OSError:
        return 0
    except Exception as e:
        print(f"get_file_mtime EXCEPTION: {str(e)}")


def get_watch_files():
    """カレントディレクトリ内のソースファイルをリストアップする"""
    try:
        return [f for f in os.listdir(".") if f.endswith(WATCH_EXTENSIONS)]
    except Exception as e:
        print(f"List UP Error -> " + str(e))


def main():
    # スクリプトのあるディレクトリに作業ディレクトリを変更
    # これにより、どこから実行してもファイルパスやMakefileが正しく認識されます
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    # PATH環境変数にMinGWのbinフォルダを追加 (cc1エラーやpkg-config対策)
    mingw_bin = os.path.dirname(BUILD_CMD[0])
    if mingw_bin and os.path.exists(mingw_bin):
        os.environ["PATH"] = mingw_bin + os.pathsep + os.environ["PATH"]

        # PKG_CONFIG_PATHを設定 (GTK+の.pcファイルが見つからないエラー対策)
        mingw_root = os.path.dirname(mingw_bin)
        pkg_config_dirs = [
            os.path.join(mingw_root, "lib", "pkgconfig"),
            os.path.join(mingw_root, "share", "pkgconfig"),
        ]

        current_pkg_path = os.environ.get("PKG_CONFIG_PATH", "")
        valid_paths = [p for p in pkg_config_dirs if os.path.exists(p)]
        if valid_paths:
            os.environ["PKG_CONFIG_PATH"] = (
                os.pathsep.join(valid_paths) + os.pathsep + current_pkg_path
            )

    # --- デバッグ: GTK+環境の確認 ---
    print("\n[Debug] Checking GTK+ environment...")
    try:
        # pkg-config が GTK+ の情報を返せるか確認
        cflags = (
            subprocess.check_output(
                ["pkg-config", "--cflags", "gtk4"], stderr=subprocess.STDOUT
            )
            .decode()
            .strip()
        )
        print(f"pkg-config cflags: {cflags}")

        # GtkSourceViewを使用している場合はこちらも確認
        try:
            subprocess.check_output(["pkg-config", "--exists", "gtksourceview-5"])
            print("GtkSourceView-5: Found")
        except:
            print("GtkSourceView-5: Not Found")
    except subprocess.CalledProcessError as e:
        print(f"[Warning] pkg-config failed: {e.output.decode().strip()}")
    except Exception as e:
        print(f"[Error] Check failed: {e}")
    print("--------------------------------\n")

    # ビルドコマンドの存在確認
    if shutil.which(BUILD_CMD[0]) is None:
        print(f"\n[Error] コマンド '{BUILD_CMD[0]}' が見つかりません。")
        print("対処法: MinGWのbinフォルダを環境変数Pathに追加するか、")
        print(
            "        スクリプト内の BUILD_CMD を絶対パス(例: r'C:\\msys64\\ucrt64\\bin\\mingw32-make.exe')に変更してください。"
        )
        return

    print("--- Task Manager Build Watcher Started ---")
    watch_files = get_watch_files()
    print(f"Watching: {', '.join(watch_files)}")
    print("Press Ctrl+C to stop.")

    # 初回のタイムスタンプ取得
    last_mtimes = {f: get_file_mtime(f) for f in watch_files}

    process = None

    # 初回ビルドと起動
    print("\n[Initial Build]")
    if subprocess.call(BUILD_CMD) == 0:
        print(f"Starting {EXECUTABLE}...")
        if os.path.exists(EXECUTABLE):
            process = subprocess.Popen(
                [os.path.abspath(EXECUTABLE)], stdout=None, stderr=None
            )
    else:
        print("Build failed.")

    try:
        while True:
            time.sleep(1)  # 1秒間隔でポーリング

            current_files = get_watch_files()
            changed_file = None
            for f in current_files:
                mtime = get_file_mtime(f)
                if mtime != last_mtimes.get(f, 0):
                    changed_file = f
                    last_mtimes[f] = mtime
                    break  # 一つでも変更があればリロードプロセスへ

            if changed_file:
                try:
                    print(f"\nChange detected in: {changed_file}")

                    # 1. 起動中のプロセスがあれば終了させる (Windowsでは必須)
                    if process and process.poll() is None:
                        print("Stopping current process...")
                        process.terminate()
                        try:
                            process.wait(timeout=2)
                        except subprocess.TimeoutExpired:
                            process.kill()

                    # 2. 再ビルド
                    print("Rebuilding...")
                    if subprocess.call(BUILD_CMD) == 0:
                        # 3. 再起動
                        print("Restarting application...")
                        process = subprocess.Popen(
                            [os.path.abspath(EXECUTABLE)], stdout=None, stderr=None
                        )
                    else:
                        print("Build failed. Waiting for fix...")
                except Exception as e:
                    print("EXCEPTION: " + str(e))

    except KeyboardInterrupt:
        print("\nExiting watcher...")
        if process and process.poll() is None:
            process.terminate()
    except Exception as e:
        print(f"EXCEPTION: {str(e)}")


if __name__ == "__main__":
    main()
