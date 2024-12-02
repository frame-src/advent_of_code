import Foundation

func readFileContent(from fileName: String, at directoryPath: String) -> String {
    let fileManager = FileManager.default

    if fileManager.fileExists(atPath: directoryPath) {
        let directoryURL = URL(fileURLWithPath: directoryPath) 
        let fileURL = directoryURL.appendingPathComponent(fileName)
        do { 
            let fileContents = try String(contentsOf: fileURL, encoding: .utf8)
            return fileContents
        } catch {
            return "Error reading file: \(error)"
        }
    } else {
        return "Failed to find directory: \(directoryPath)"
    }
}

func splitContent(input: String) -> ([Int], [Int]) {
    let lines = input.split(separator: "\n")
    var left : [Int] = []
    var right : [Int] = [] 

    for line in lines {
        let numbers = line.split(separator: " ")
        if let leftNumber = Int(numbers[0]), let rightNumber = Int(numbers[1]) {
            left.append(leftNumber)
            right.append(rightNumber)
        }
    }
    return (left,right)
}

func main() {
    let fileName = "input"

    let fileManager = FileManager.default
    let currentDirectoryPath = fileManager.currentDirectoryPath
    var content : String = ""
    content = readFileContent(from: fileName, at: currentDirectoryPath)

    let (left, right) = splitContent( input:content )
    print (left)
    print (right)

}

main()
