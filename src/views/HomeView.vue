<template>
  <div class="home-page">
    <!-- Navbar -->
    <header class="navbar">
      <div class="logo">
        <v-icon>mdi-cloud</v-icon>
        IBEET Cloud Storage
      </div>

      <div class="user-area">
        <span>Welcome, User</span>

        <v-btn variant="text" color="white" prepend-icon="mdi-logout" @click="logout">
          Logout
        </v-btn>
      </div>
    </header>

    <!-- Main -->
    <main class="content">
      <!-- Title -->
      <div class="title-row">
        <div>
          <h1>My Files</h1>
          <p>Manage your files in the cloud</p>
        </div>

        <div class="actions">
          <v-btn variant="outlined" prepend-icon="mdi-folder-plus" @click="openFolderDialog">
            New Folder
          </v-btn>

          <!-- Upload -->
          <v-btn color="primary" prepend-icon="mdi-upload" @click="openFilePicker"> Upload </v-btn>

          <!-- 隱藏的檔案選擇器 -->
          <input ref="fileInput" type="file" hidden @change="handleFileUpload" />
        </div>
      </div>

      <!-- Breadcrumb -->
      <div class="breadcrumb">
        <v-icon size="20"> mdi-home </v-icon>

        <span>My Files</span>
      </div>

      <!-- File List -->
      <div class="file-area">
        <!-- New Folder Dialog -->
        <v-dialog v-model="folderDialog" max-width="450">
          <v-card>
            <v-card-title> Create New Folder </v-card-title>

            <v-card-text>
              <v-text-field
                v-model="newFolderName"
                label="Folder Name"
                variant="outlined"
                prepend-inner-icon="mdi-folder"
                @keyup.enter="createFolder"
              />
            </v-card-text>

            <v-card-actions>
              <v-spacer />

              <v-btn variant="text" @click="folderDialog = false"> Cancel </v-btn>

              <v-btn color="primary" variant="flat" @click="createFolder"> Create </v-btn>
            </v-card-actions>
          </v-card>
        </v-dialog>

        <!-- Rename Dialog -->
        <v-dialog v-model="renameDialog" max-width="450">
          <v-card>
            <v-card-title> Rename File </v-card-title>

            <v-card-text>
              <v-text-field
                v-model="renameName"
                label="New Name"
                variant="outlined"
                prepend-inner-icon="mdi-pencil"
                @keyup.enter="renameFile"
              />
            </v-card-text>

            <v-card-actions>
              <v-spacer />

              <v-btn variant="text" @click="renameDialog = false"> Cancel </v-btn>

              <v-btn color="primary" @click="renameFile"> Rename </v-btn>
            </v-card-actions>
          </v-card>
        </v-dialog>

        <!-- Header -->
        <div class="file-header">
          <span>Name</span>
          <span>Type</span>
          <span>Action</span>
        </div>

        <!-- Files -->
        <div v-for="file in files" :key="file.id" class="file-item">
          <div class="file-name">
            <v-icon size="38" :color="getFileColor(file.name)">
              {{ getFileIcon(file.name) }}
            </v-icon>

            <div>
              <strong>
                {{ file.name }}
              </strong>

              <p>
                {{ file.type }}
              </p>
            </div>
          </div>

          <span>
            {{ file.type }}
          </span>

          <v-menu>
            <template #activator="{ props }">
              <v-btn icon="mdi-dots-vertical" variant="text" v-bind="props" />
            </template>

            <v-list>
              <v-list-item
                prepend-icon="mdi-download"
                title="Download"
                @click="downloadFile(file)"
              />

              <v-list-item
                prepend-icon="mdi-pencil"
                title="Rename"
                @click="openRenameDialog(file)"
              />

              <v-list-item prepend-icon="mdi-delete" title="Delete" @click="deleteFile(file)" />
            </v-list>
          </v-menu>
        </div>

        <!-- 沒有檔案 -->
        <div v-if="files.length === 0" class="empty">
          <v-icon size="60"> mdi-folder-open-outline </v-icon>

          <p>No files yet</p>
        </div>
      </div>
    </main>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import { useRouter } from 'vue-router'

const router = useRouter()

// ==============================
// 使用者檔案
// ==============================

const files = ref([
  {
    id: 1,
    name: 'Homework',
    type: 'Folder',
  },
  {
    id: 2,
    name: 'report.pdf',
    type: 'PDF',
  },
  {
    id: 3,
    name: 'image.png',
    type: 'Image',
  },
])

// ==============================
// File Input
// ==============================

const fileInput = ref(null)

// ==============================
// New Folder
// ==============================

const folderDialog = ref(false)

const newFolderName = ref('')

// 開啟新增資料夾視窗
function openFolderDialog() {
  newFolderName.value = ''

  folderDialog.value = true
}

// 建立資料夾
function createFolder() {
  const name = newFolderName.value.trim()

  // 沒有輸入名稱
  if (!name) {
    return
  }

  files.value.push({
    id: Date.now(),
    name: name,
    type: 'Folder',
  })

  // 關閉視窗
  folderDialog.value = false

  // 清空輸入
  newFolderName.value = ''
}

// 開啟檔案選擇器
function openFilePicker() {
  fileInput.value.click()
}

// 使用者選擇檔案
function handleFileUpload(event) {
  const selectedFile = event.target.files[0]

  if (!selectedFile) {
    return
  }

  // 判斷檔案類型
  const type = getFileType(selectedFile.name)

  // 加入畫面
  files.value.push({
    id: Date.now(),
    name: selectedFile.name,
    type: type,
  })

  // 清除 input
  event.target.value = ''
}

// ==============================
// Rename
// ==============================

const renameDialog = ref(false)

const renameName = ref('')

const selectedFile = ref(null)

// 開啟 Rename
function openRenameDialog(file) {
  selectedFile.value = file

  renameName.value = file.name

  renameDialog.value = true
}

// 執行 Rename
function renameFile() {
  const name = renameName.value.trim()

  if (!name || !selectedFile.value) {
    return
  }

  selectedFile.value.name = name

  renameDialog.value = false

  selectedFile.value = null
}

// ==============================
// Delete
// ==============================

function deleteFile(file) {
  const confirmed = confirm(`Delete "${file.name}"?`)

  if (!confirmed) {
    return
  }

  files.value = files.value.filter((item) => item.id !== file.id)
}

// ==============================
// Download
// ==============================

function downloadFile(file) {
  alert(`Download "${file.name}" will be implemented after backend integration.`)
}
// ==============================
// 判斷檔案類型
// ==============================

function getFileType(fileName) {
  const extension = fileName.split('.').pop().toLowerCase()

  if (extension === 'pdf') {
    return 'PDF'
  }

  if (extension === 'png' || extension === 'jpg' || extension === 'jpeg' || extension === 'gif') {
    return 'Image'
  }

  if (extension === 'doc' || extension === 'docx') {
    return 'Word'
  }

  if (extension === 'xls' || extension === 'xlsx') {
    return 'Excel'
  }

  if (extension === 'zip' || extension === 'rar' || extension === '7z') {
    return 'Archive'
  }

  return 'File'
}

// ==============================
// Icon
// ==============================

function getFileIcon(fileName) {
  const type = getFileType(fileName)

  if (type === 'Folder') {
    return 'mdi-folder'
  }

  if (type === 'PDF') {
    return 'mdi-file-pdf-box'
  }

  if (type === 'Image') {
    return 'mdi-file-image'
  }

  if (type === 'Word') {
    return 'mdi-file-word'
  }

  if (type === 'Excel') {
    return 'mdi-file-excel'
  }

  if (type === 'Archive') {
    return 'mdi-folder-zip'
  }

  return 'mdi-file-document'
}

// ==============================
// Icon Color
// ==============================

function getFileColor(fileName) {
  const type = getFileType(fileName)

  if (type === 'Folder') {
    return 'orange'
  }

  if (type === 'PDF') {
    return 'red'
  }

  if (type === 'Image') {
    return 'blue'
  }

  if (type === 'Word') {
    return 'indigo'
  }

  if (type === 'Excel') {
    return 'green'
  }

  if (type === 'Archive') {
    return 'deep-purple'
  }

  return 'grey'
}

// ==============================
// Logout
// ==============================

function logout() {
  router.push('/')
}
</script>

<style scoped>
.home-page {
  min-height: 100vh;
  background: #f5f7fa;
}

/* Navbar */

.navbar {
  height: 70px;

  background: #1976d2;
  color: white;

  display: flex;
  align-items: center;
  justify-content: space-between;

  padding: 0 40px;

  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.15);
}

.logo {
  display: flex;
  align-items: center;
  gap: 10px;

  font-size: 22px;
  font-weight: bold;
}

.user-area {
  display: flex;
  align-items: center;
  gap: 15px;
}

/* Main */

.content {
  max-width: 1100px;

  margin: auto;

  padding: 40px;
}

/* Title */

.title-row {
  display: flex;

  justify-content: space-between;
  align-items: center;

  margin-bottom: 25px;
}

.title-row h1 {
  margin: 0;

  font-size: 32px;

  color: #222;
}

.title-row p {
  margin-top: 6px;

  color: #777;
}

.actions {
  display: flex;

  gap: 12px;
}

/* Breadcrumb */

.breadcrumb {
  display: flex;

  align-items: center;

  gap: 8px;

  margin-bottom: 15px;

  color: #555;
}

/* File Area */

.file-area {
  background: white;

  border-radius: 15px;

  overflow: hidden;

  box-shadow: 0 3px 12px rgba(0, 0, 0, 0.08);
}

/* Header */

.file-header {
  display: grid;

  grid-template-columns: 1fr 150px 100px;

  padding: 18px 25px;

  background: #fafafa;

  color: #777;

  font-weight: bold;

  border-bottom: 1px solid #eee;
}

/* File */

.file-item {
  display: grid;

  grid-template-columns: 1fr 150px 100px;

  align-items: center;

  padding: 20px 25px;

  border-bottom: 1px solid #eee;

  transition: background 0.2s;
}

.file-item:hover {
  background: #f8faff;
}

.file-name {
  display: flex;

  align-items: center;

  gap: 18px;
}

.file-name strong {
  font-size: 17px;

  color: #222;
}

.file-name p {
  margin: 4px 0 0;

  color: #999;

  font-size: 14px;
}

/* Empty */

.empty {
  padding: 70px;

  text-align: center;

  color: #999;
}

.empty p {
  margin-top: 15px;

  font-size: 18px;
}
</style>
